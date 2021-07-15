# A Symmetric Cryptographic Encryption and Decryption in Python
# done b @Sri_Programmer
# Python v3.7.2

# imports 

import os
import sys

from termcolor import colored,cprint

class Encryption:

	def __init__(self,filename,key):	# Constructor
		self.filename = filename
		self.key = key

	def encryption(self): # Allows us to perfrom file operation

		try:
			original_information = open(self.filename,'rb')

		except (IOError, FileNotFoundError):
			print('File with name {} is not found.')
			sys.exit(0)

		try:

			encrypted_file_name = 'cipher_' + self.filename
			encrypted_file_object = open(encrypted_file_name,'wb')

			content = original_information.read()
			content = bytearray(content)


			print('Encryption Process is in progress...!')
			for i,val in enumerate(content):
				content[i] = val ^ key
			
			encrypted_file_object.write(content)
			

		except Exception:
			print('Something went wrong with code')
		finally:
			encrypted_file_object.close()
			original_information.close()






file = sys.argv[1]
key = int(sys.argv[2])
E1 = Encryption(file,key)
E1.encryption()
print(file,key)
print("[+] Encryption is done Sucessfully...! ")

