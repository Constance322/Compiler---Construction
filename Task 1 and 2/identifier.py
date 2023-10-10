# -*- coding: utf-8 -*-
"""Identifier.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1xeHqsu8_cydGyN4iJx2pI4IAldGY6j7s
"""

import re

def is_valid_identifier(identifier):
    # Regular expression pattern for a valid identifier
    pattern = r'^[a-zA-Z_][a-zA-Z0-9_]*$'

    # Use re.match to check if the identifier matches the pattern
    if re.match(pattern, identifier):
        return True
    else:
        return False

# Input identifier to be tested
input_identifier = input("Enter an identifier: ")

if is_valid_identifier(input_identifier):
    print(f"{input_identifier} is a valid identifier.")
else:
    print(f"{input_identifier} is not a valid identifier.")