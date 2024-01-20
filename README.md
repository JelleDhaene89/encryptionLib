# Exercise: Implementing the Cipher Class

## Objective:
The objective of this exercise is to implement the functionality of the `Cipher` class based on the provided header file (`Cipher.h`) and the provided test class to validate the implementation.

## Instructions:

1. **Install Dependencies:**

   - **Qt Libraries:**
     You can download and install the Qt libraries from the official Qt website: [Qt Downloads](https://www.qt.io/download). Follow the installation instructions for your specific platform.

   - **Conan:**
     Install Conan, the C/C++ package manager, using pip (Python package manager) with the following command:
     ```
     pip install conan
     ```

   - **CMake:**
     CMake is a cross-platform build system. Download and install CMake from the official website: [CMake Downloads](https://cmake.org/download/). Follow the installation instructions for your platform.

   - **Ninja:**
     Ninja is a fast and efficient build tool that can be used with CMake. You can download Ninja from the official GitHub repository: [Ninja GitHub Releases](https://github.com/ninja-build/ninja/releases). Follow the installation instructions for your platform.


2. **implement the CPP File:**
   Start by implementing the CPP file (`Cipher.cpp`) that corresponds to the provided header file (`Cipher.h`).

3. **Include Necessary Headers:**
   Include the required headers and dependencies, such as the necessary Qt headers and any external cryptographic libraries or algorithms you plan to use.

4. **Add Non-Qt Dependencies as Conan Packages:**
   If you need to include non-Qt dependencies, consider adding them as Conan packages. Conan is a C/C++ package manager that can help manage and install external libraries. Ensure that your project's Conan configuration includes the necessary packages.

5. **Implement Signature Generation:**
   Implement the `signature` function, which computes a digital signature for a given file. You can use cryptographic libraries or algorithms to create a unique signature for the file's contents. Ensure that the generated signature is returned as a `QByteArray`.

6. **Implement Signature Verification:**
   Implement the `verifySignature` function to check if a provided digital signature matches the file's actual content. Verify that the file has not been altered since it was signed. You may need to use cryptographic libraries or algorithms to perform this verification.

7. **Implement Encryption:**
   Implement the `encrypt` function, which should encrypt the given plaintext data using the password-derived key. You can use encryption algorithms like AES for this purpose. Ensure that the encrypted data is returned as a `QByteArray`.

8. **Implement Decryption:**
   Implement the `decrypt` function, which should decrypt the given ciphertext data using the password-derived key. Use the same encryption algorithm as in the encryption step. Return the decrypted data as a `QByteArray`.

9. **Private Functions:**
   You are allowed to add private functions and member variables to the class as needed to implement the cryptographic operations. Ensure that these private functions are appropriately documented.

10. **Testing:**
    Use the provided test class to validate the functionality of the `Cipher` class. Run the tests and make sure they pass successfully. You can also add additional tests if needed to cover various scenarios.

11. **Documentation:**
    Provide comments within the CPP file to explain the purpose of each implemented function, its input parameters, and the expected output.


### Additional Challenges (Optional):

- Implement password handling securely, considering best practices for password storage and usage.
- Add error handling and robustness to your cryptographic operations.
- Explore different cryptographic algorithms and key derivation techniques for improved security.
