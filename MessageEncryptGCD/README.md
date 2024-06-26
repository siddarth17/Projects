Function: The secretMessages program is designed to handle secure communication by encrypting and decrypting 
messages using RSA, a widely recognized asymmetric encryption method. This program allows users to encrypt 
plain text into a cipher and decrypt it back to readable text, ensuring confidentiality and security in file transfers.

Explanation of Commands:

ENCRYPT [filename] [n] [message]: This command encrypts a given message using RSA encryption parameters and 
writes the encrypted message to the specified filename. Here, [n] represents a key component in the RSA encryption 
algorithm, typically the product of two prime numbers p and q which must be kept secure.

DECRYPT [input] [output]: This command reads an encrypted message from the [input] file, decrypts it using the 
RSA decryption process, and writes the decrypted message to the [output] file, effectively restoring the original text.

