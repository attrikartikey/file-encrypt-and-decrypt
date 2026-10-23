# File Encrypt / Decrypt Tool

A small C++17 command-line program that encrypts or decrypts every file inside a directory (including subdirectories) using a numeric key from a `.env` file.

> **Warning:** files are modified **in place**. Always run it on a copy of your data. This is a learning project, not real security (see [Limitations](#limitations)).

## How it works

1. You enter a directory path and an action (`ENCRYPT` or `DECRYPT`).
2. The program walks the directory recursively and queues one task per regular file.
3. Each task is run through `executeCryption`, which shifts every byte of the file by the key (`+ key` to encrypt, `- key` to decrypt, modulo 256).
4. The key is read from the `.env` file in the working directory.

## Project structure

```
.
├── main.cpp                         # interactive entry point
├── Makefile
├── .env.example                     # copy to .env and set your key
└── main/application/
    ├── encryptDecrypt/
    │   ├── Cryption.cpp / .hpp      # the byte-shift cipher
    │   └── CryptionMain.cpp         # standalone cryption executable
    ├── file_handling/
    │   ├── IO.cpp / .hpp            # opens files as binary streams
    │   └── readEnv.cpp              # reads the key from .env
    └── processes/
        ├── ProcessManagement.cpp / .hpp   # task queue
        └── Task.hpp                       # task = file stream + action + path
```

## Requirements

- A C++17 compiler with `<filesystem>` support (**GCC 8+**, GCC 9+ recommended)
- GNU Make (`make`, or `mingw32-make` on Windows)

## Setup

```bash
git clone https://github.com/<your-username>/<repo-name>.git
cd <repo-name>
cp .env.example .env      # Windows: copy .env.example .env
```

Edit `.env` and put a whole number in it (for example `1234`). Use the **same** key to decrypt that you used to encrypt.

## Build

```bash
make                      # Windows with MinGW: mingw32-make
```

This produces two executables:

- `encrypt_decrypt`: the interactive program
- `cryption`: processes a single file

Clean up with `make clean`.

## Usage

Run from the project root, so the program can find `.env`.

### Interactive (whole directory)

```
$ ./encrypt_decrypt
Enter the directory path:
my_folder
Enter the action (ENCRYPT , DECRYPT):
ENCRYPT
```

The action must be typed in capitals: anything other than `ENCRYPT` is treated as `DECRYPT`.

### Single file

```bash
./cryption "path/to/file.txt,ENCRYPT"
./cryption "path/to/file.txt,DECRYPT"
```

## Limitations

- **Not secure.** A fixed byte shift is a Caesar-style cipher and is trivially broken. Don't use it to protect real data.
- Files are overwritten in place, with no backup.
- Running DECRYPT on a file that was never encrypted (or with a different key) scrambles it.
- Tasks run one after another; there is no parallel processing yet.

## Ideas for improvement

- Validate the action and reject unknown input
- Use a real cipher such as AES (for example via OpenSSL or libsodium)
- Run tasks in parallel
- Write output to a new file instead of overwriting

## License

Add a license of your choice (for example MIT) as a `LICENSE` file.
