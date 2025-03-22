import os
import shutil
import hashlib
from datetime import datetime

def list_files(directory):
    """Menampilkan semua file dalam direktori."""
    for root, _, files in os.walk(directory):
        for file in files:
            print(os.path.join(root, file))

def organize_files(directory):
    """Mengelompokkan file berdasarkan ekstensi."""
    for file in os.listdir(directory):
        file_path = os.path.join(directory, file)
        if os.path.isfile(file_path):
            ext = file.split('.')[-1]
            target_dir = os.path.join(directory, ext.upper())
            os.makedirs(target_dir, exist_ok=True)
            shutil.move(file_path, os.path.join(target_dir, file))

def search_files(directory, keyword):
    """Mencari file berdasarkan nama."""
    for root, _, files in os.walk(directory):
        for file in files:
            if keyword.lower() in file.lower():
                print(os.path.join(root, file))

def rename_files(directory, prefix):
    """Mengganti nama file dengan prefix tertentu."""
    for file in os.listdir(directory):
        file_path = os.path.join(directory, file)
        if os.path.isfile(file_path):
            new_name = f"{prefix}_{file}"
            os.rename(file_path, os.path.join(directory, new_name))

def delete_duplicates(directory):
    """Menghapus file duplikat berdasarkan hash."""
    hashes = {}
    for root, _, files in os.walk(directory):
        for file in files:
            file_path = os.path.join(root, file)
            with open(file_path, 'rb') as f:
                file_hash = hashlib.md5(f.read()).hexdigest()
            if file_hash in hashes:
                os.remove(file_path)
                print(f"Deleted duplicate: {file_path}")
            else:
                hashes[file_hash] = file_path

def backup_files(source, backup_dir):
    """Membuat backup otomatis saat ada perubahan."""
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    backup_path = os.path.join(backup_dir, f"backup_{timestamp}")
    shutil.copytree(source, backup_path)
    print(f"Backup dibuat di {backup_path}")

if __name__ == "__main__":
    dir_path = input("Masukkan direktori target: ")
    while True:
        print("\n1. List Files\n2. Organize Files\n3. Search Files\n4. Rename Files\n5. Delete Duplicates\n6. Backup Files\n7. Exit")
        choice = input("Pilih opsi: ")
        
        if choice == "1":
            list_files(dir_path)
        elif choice == "2":
            organize_files(dir_path)
        elif choice == "3":
            keyword = input("Masukkan kata kunci pencarian: ")
            search_files(dir_path, keyword)
        elif choice == "4":
            prefix = input("Masukkan prefix rename: ")
            rename_files(dir_path, prefix)
        elif choice == "5":
            delete_duplicates(dir_path)
        elif choice == "6":
            backup_dir = input("Masukkan direktori backup: ")
            backup_files(dir_path, backup_dir)
        elif choice == "7":
            break
        else:
            print("Pilihan tidak valid.")