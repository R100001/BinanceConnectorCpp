
#include "authentication.hpp"

#include <string>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include <sstream>
#include <openssl/hmac.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

//------------------------------------------------------------------------------------

static std::string to_hex_string(unsigned char const * data, size_t const length) {
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    for (size_t i = 0; i < length; ++i) {
        oss << std::setw(2) << static_cast<int>(data[i]);
    }
    return oss.str();
}

//------------------------------------------------------------------------------------

std::string hmac_signature(std::string_view secret, std::string_view payload) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    unsigned int digest_len;

    HMAC(EVP_sha256(), 
         secret.data(), secret.size(), 
         reinterpret_cast<const unsigned char*>(payload.data()), payload.size(), 
         digest, &digest_len);

    if (digest_len != SHA256_DIGEST_LENGTH) {
        throw std::runtime_error("HMAC computation failed");
    }

    return to_hex_string(digest, digest_len);
}

//------------------------------------------------------------------------------------

BIO *createBIOForPrivateKey(std::string_view private_key) {
    BIO *bio = BIO_new_mem_buf(private_key.data(), private_key.size());
    if (!bio) {
        throw std::runtime_error("Failed to create BIO for private key");
    }
    return bio;
}

//------------------------------------------------------------------------------------

EVP_PKEY* loadPrivateKeyFromBIO(BIO* bio, std::string_view private_key_pass) {
    EVP_PKEY* pkey = nullptr;
    
    pkey = PEM_read_bio_PrivateKey(bio, nullptr, nullptr, private_key_pass.empty() ? nullptr : const_cast<char*>(private_key_pass.data()));
    
    if (!pkey) {
        throw std::runtime_error("Failed to load RSA private key");
    }
    
    // Verify that the key is actually an ED25519 key (optional but recommended)
    if (EVP_PKEY_get_base_id(pkey) != EVP_PKEY_ED25519) {
        EVP_PKEY_free(pkey);
        throw std::runtime_error("Loaded key is not an ED25519 key");
    }
    
    return pkey;
}

//------------------------------------------------------------------------------------

static std::string base64_encode(unsigned char const * data, size_t const length) {
    BIO* bio = BIO_new(BIO_s_mem());
    BIO* b64 = BIO_new(BIO_f_base64());
    bio = BIO_push(b64, bio);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); // No newlines
    BIO_write(bio, data, length);
    BIO_flush(bio);

    BUF_MEM* buffer;
    BIO_get_mem_ptr(bio, &buffer);
    std::string result(buffer->data, buffer->length);

    BIO_free_all(bio);
    return result;
}

//------------------------------------------------------------------------------------

std::string signPayload(EVP_PKEY* pkey, std::string_view payload) {

    // Create an EVP_MD_CTX for signing
    EVP_MD_CTX* md_ctx = EVP_MD_CTX_new();
    if (!md_ctx) {
        throw std::runtime_error("Failed to create EVP_MD_CTX");
    }

    // Initialize the signing operation
    if (EVP_DigestSignInit(md_ctx, nullptr, nullptr, nullptr, pkey) != 1) {
        EVP_MD_CTX_free(md_ctx);
        throw std::runtime_error("Failed to initialize signing");
    }

    // Get signature size (first call with nullptr)
    size_t sig_len;
    if (EVP_DigestSign(md_ctx, nullptr, &sig_len, 
                       reinterpret_cast<const unsigned char*>(payload.data()), 
                       payload.size()) != 1) {
        EVP_MD_CTX_free(md_ctx);
        throw std::runtime_error("Failed to get signature length");
    }

    // Allocate space and create the signature
    std::vector<unsigned char> signature(sig_len);
    if (EVP_DigestSign(md_ctx, signature.data(), &sig_len,
                       reinterpret_cast<const unsigned char*>(payload.data()),
                       payload.size()) != 1) {
        EVP_MD_CTX_free(md_ctx);
        throw std::runtime_error("Failed to sign payload");
    }

    // Clean up
    EVP_MD_CTX_free(md_ctx);

    // Resize to actual signature length
    signature.resize(sig_len);

    // Return base64-encoded signature
    return base64_encode(signature.data(), signature.size());
}

//------------------------------------------------------------------------------------

#include <iostream>
std::string ed25519_signature(std::string_view private_key, std::string_view payload, 
                          std::string_view private_key_passphrase = "") {

    std::cout << "Payload to sign: " << payload << std::endl;

    BIO* bio = createBIOForPrivateKey(private_key);

    EVP_PKEY* pkey = loadPrivateKeyFromBIO(bio, private_key_passphrase);
    
    BIO_free(bio);
    
    std::string const signature = signPayload(pkey, payload);

    EVP_PKEY_free(pkey);

    return signature;
}

//------------------------------------------------------------------------------------
