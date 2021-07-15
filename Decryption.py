# A Symmetric Cryptographic Encryption and Decryption in Python
# done b @Sri_Programmer
# Python v3.7.2

# imports 

import os
import sys

from termcolor import colored,cprint

class Decryption:

	def __init__(self,filename,key):
		self.filename = filename
		self.key = key

	def decryption(self):	# produces the original result
		
		try:
			encrypted_file_object = open(self.filename,'rb')

		except (FileNotFoundError,IOError):
			print('File with name {} is not found')
			sys.exit(0)

		try:

			decrypted_file = "Decrypted.jfif";

			decrypted_file_object = open(decrypted_file,'wb')

			cipher_text = encrypted_file_object.read()

			cipher_text = bytearray(cipher_text)

			print('Decryption Process is in progress...!')

			for i,val in enumerate(cipher_text):
				cipher_text[i] = val^key
		
			decrypted_file_object.write(cipher_text)
			

		except Exception:
				print('Some problem with Ciphertext unable to handle.')

		finally:
			encrypted_file_object.close()
			decrypted_file_object.close()


			

		

file = sys.argv[1]
key = int(sys.argv[2])
D1 = Decryption(file,key)
D1.decryption()
print(" [+] Decryption is done Sucessfully...!")
			
