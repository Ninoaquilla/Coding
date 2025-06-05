import os
import random
import string

def generate_random_string(length=15):
    characters = string.ascii_letters + string.digits
    return ''.join(random.choices(characters, k=length))

def save_to_file(folder='output', filename='random_string.txt'):
    if not os.path.exists(folder):
        os.makedirs(folder)
    
    random_string = generate_random_string()
    file_path = os.path.join(folder, filename)
    
    with open(file_path, 'w') as file:
        file.write(random_string)
    
    print(f"Kalimat acak disimpan di: {file_path}")
    return file_path

if __name__ == "__main__":
    save_to_file()
