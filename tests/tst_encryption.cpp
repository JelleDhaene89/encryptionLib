#include <QtTest>
#include "cipher.h"

/**
 * @class EncryptionTest
 * @brief Test suite for testing cryptographic functions using the Cipher class.
 */
class EncryptionTest : public QObject
{
    Q_OBJECT

public:
    EncryptionTest(QObject *parent = nullptr)
        : QObject(parent)
        , m_cipher(new Cipher("IAmAStr0ngPassW0rd")) // Initialize Cipher with a password
        , m_tempDir()
        , m_filePath()
        , m_license("{license: feature1, expdate: 1726142400}")
        , m_temperedLicence("{license: feature1, expdate: 1757678400}")
    {}
    virtual ~EncryptionTest() {}

private Q_SLOTS:
    void init(); // Initialize test environment
    void cleanup(); // Clean up after each test case

    void testSignatureGenerationAndVerification();
    void testSignatureInvalidityOnFileChange();

    void testEncryptionAndDecryption();
    void testAttack();
    void testRainbowProtection();
    void testUninitializedCipher();

private:
    QScopedPointer<Cipher> m_cipher;
    QDir m_tempDir;
    QString m_filePath;
    QByteArray m_license;
    QByteArray m_temperedLicence;

    bool flush(const QString &filepath, const QByteArray &data);
};

void EncryptionTest::init()
{
    // create a temporary directory
    QTemporaryDir temp;
    temp.setAutoRemove(false);
    m_tempDir = QDir(temp.path());

    // create a license file to sign
    m_filePath =  m_tempDir.absoluteFilePath("license.txt");
    this->flush(m_filePath, m_license);
}

void EncryptionTest::cleanup()
{
    m_tempDir.removeRecursively();
}

/**
 * @brief Test signature generation and verification.
 */
void EncryptionTest::testSignatureGenerationAndVerification()
{
    QByteArray signature = m_cipher->signature(m_filePath);
    bool isValid = m_cipher->verifySignature(m_filePath, signature);

    QVERIFY(isValid); // The signature should be valid
}

/**
 * @brief Test signature invalidation on file change.
 */
void EncryptionTest::testSignatureInvalidityOnFileChange()
{
    // create a signature of the orginal license file
    QByteArray signature = m_cipher->signature(m_filePath);

    // temper with the license file
    this->flush(m_filePath, m_temperedLicence);

    // Validate the license file
    bool isValid = m_cipher->verifySignature(m_filePath, signature);

    QVERIFY(!isValid); // The signature should be invalid
}

/**
 * @brief Test encryption and decryption functionality.
 */
void EncryptionTest::testEncryptionAndDecryption()
{
    // Define some plaintext
    QByteArray plaintext = "This is a test message.";

    // Encrypt the plaintext
    QByteArray ciphertext = m_cipher->encrypt(plaintext);

    // Decrypt the ciphertext
    QByteArray decryptedText = m_cipher->decrypt(ciphertext);

    // The decrypted text should match the original plaintext
    QCOMPARE(plaintext, decryptedText);
}

/**
 * @brief Test an attack scenario with a wrong password.
 */
void EncryptionTest::testAttack() {
    // Attempt an attack with a wrong password
    Cipher attacker("WrongPassword");

    // Define a test plaintext
    QByteArray plaintext = "This is a test message.";

    // Encrypt the plaintext with the wrong password
    QByteArray ciphertext = m_cipher->encrypt(plaintext);

    // Attempt to decrypt with the wrong password
    QByteArray decryptedText = attacker.decrypt(ciphertext);

    // The decrypted text should not match the original plaintext
    QVERIFY(plaintext != decryptedText);
}

/**
 * @brief Test protection against rainbow table attacks.
 */
void EncryptionTest::testRainbowProtection() {
    // Define a test plaintext
    QByteArray plaintext = "This is a test message.";

    // Encrypt the same plaintext twice
    QByteArray ciphertext1 = m_cipher->encrypt(plaintext);
    QByteArray ciphertext2 = m_cipher->encrypt(plaintext);

    // The ciphertexts should not be the same
    QVERIFY(ciphertext1 != ciphertext2);
}

/**
 * @brief Test decryption with an uninitialized Cipher instance.
 */
void EncryptionTest::testUninitializedCipher() {
    // Try to decrypt with an uninitialized Cipher instance
    Cipher uninitializedCipher("");

    // Define a test ciphertext
    QByteArray ciphertext = "Some ciphertext";

    // Attempt to decrypt with an uninitialized cipher
    QByteArray decryptedText = uninitializedCipher.decrypt(ciphertext);

    // Decryption should fail, and the result should be empty
    QVERIFY(decryptedText.isEmpty());
}

/**
 * @brief Helper function to flush data to a file.
 * @param filepath The path of the file to write.
 * @param data The data to write to the file.
 * @return True if the data was successfully written, false otherwise.
 */
bool EncryptionTest::flush(const QString &filepath, const QByteArray &data)
{
    QFile file(filepath);

    if (!file.open(QFile::WriteOnly))
    {
        qWarning() << "Error opening" << filepath <<  "for writing";
        return false;
    }
    if (file.write(data) < 0)
    {
        qWarning() << "Error writing to" << filepath;
        file.close();
        return false;
    }

    file.close();
    return true;
}

QTEST_GUILESS_MAIN(EncryptionTest)

#include "tst_encryption.moc"
