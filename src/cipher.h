#pragma once

// Qt headers
#include <QByteArray>

// library headers
#include "encryption_export.h"

/**
 * @class Cipher
 * @brief The Cipher class provides cryptographic functionalities including signature generation and verification, encryption, and decryption.
 *
 * This class encapsulates cryptographic operations using a password-based approach. The password is used in generating a key for encryption and decryption.
 * It also supports generating and verifying digital signatures for files. The operations are intended to be secure and efficient, suitable for a variety of
 * cryptographic needs.
 *
 * Note: The public interface of this class should not be changed. Additional functions and parameters can be added as needed in the private section.
 */
class ENCRYPTION_EXPORT Cipher
{
public:
    /**
     * @brief Constructor for the Cipher class that initializes the cipher with a password.
     *
     * @param password The password used for generating the encryption/decryption key.
     */
    Cipher(const QString &password);

    /**
     * @brief Generates a digital signature for a given file.
     *
     * This function computes a digital signature for the specified file. The signature is
     * unique to the file's contents and can be used to verify its integrity and authenticity.
     *
     * @param filename The path to the file location to generate the signature for.
     * @return QByteArray The digital signature of the file.
     */
    QByteArray signature(const QString &filename);

    /**
     * @brief Verifies the digital signature of a file.
     *
     * This function checks if the provided digital signature matches the file's actual content,
     * ensuring that the file has not been altered since it was signed.
     *
     * @param filename The path to the file location to verify the signature against.
     * @param signature The digital signature to verify.
     * @return bool True if the signature is valid, False otherwise.
     */
    bool verifySignature(const QString &filename, const QByteArray &signature);

    /**
     * @brief Encrypts plaintext data.
     *
     * This function encrypts the given plaintext using the initialized password-derived key.
     * The encrypted data is returned in a QByteArray.
     *
     * @param plainText The plaintext data to encrypt.
     * @return QByteArray The encrypted data.
     */
    QByteArray encrypt(QByteArray &plainText);

    /**
     * @brief Decrypts ciphertext data.
     *
     * This function decrypts the given ciphertext using the initialized password-derived key.
     * The decrypted data is returned in a QByteArray.
     *
     * @param cipher The ciphertext data to decrypt.
     * @return QByteArray The decrypted data.
     */
    QByteArray decrypt(QByteArray &cipher);

private:
    QString m_password;  // The password used for key generation in cryptographic operations.

    // Additional private functions and member variables can be added here as needed.
};
