Function: The secretMessages program is designed to handle secure communication by encrypting and decrypting 
messages using RSA, a widely recognized asymmetric encryption method. This program allows users to encrypt 
plain text into a cipher and decrypt it back to readable text, ensuring confidentiality and security in file transfers.

Explanation of Commands:

ENCRYPT [filename] [n] [message]: This command encrypts a given message using RSA encryption parameters and 
writes the encrypted message to the specified filename. Here, [n] represents a key component in the RSA encryption 
algorithm, typically the product of two prime numbers p and q which must be kept secure.

DECRYPT [input] [output]: This command reads an encrypted message from the [input] file, decrypts it using the 
RSA decryption process, and writes the decrypted message to the [output] file, effectively restoring the original text.

Example Walkthrough of Encryption/Decryption:

Encryption Setup:
Command: ./rsa 881 911

p value for RSA: 881
q value for RSA: 911
Encrypting a Message:
Command: ENCRYPT secret.txt 801791 "keep this safe"

Target File: secret.txt where the encrypted message will be stored
n Value: 801791 (calculated as pq, i.e., 881911)
Message: "keep this safe"
Contents of secret.txt after encryption:
123456 789012 345678 901234 567890
Decrypting a Message:
Command: DECRYPT secret.txt plain.txt

Source File: secret.txt containing the encrypted message
Output File: plain.txt where the decrypted message will be restored

Contents of plain.txt after decryption:
keep this safe
