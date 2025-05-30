# Cryptographic Rock-Paper-Scissors

## Game Overview

This is a trustless implementation of Rock-Paper-Scissors using cryptographic hash functions. The game works as follows:

Player 1 chooses a number (1 = rock, 2 = paper, 3 = scissors), and is given a nonce and a hash.
Player 1 sends the hash to Player 2.

Player 2 does the same, and sends the hash to Player 1.
Now when both players has their opponents hash, they share their choice and nonce.

Both players can now verify if the opponent is trustworthy or not.

## Requirements

- C compiler (gcc or clang)
- CMake (version 4.0.2 or higher)
- libsodium (cryptographic library)

## Building the Application

### Installing Dependencies

#### macOS
```bash
brew install libsodium cmake
```

#### Ubuntu/Debian
```bash
apt-get install libsodium-dev cmake
```

#### Fedora/RHEL
```bash
dnf install libsodium-devel cmake
```

### Compiling

```bash
# Create a build directory
mkdir build
cd build

# Configure and build
cmake ..
make
```

This will create two executables: `commit` and `verify`.

## How to Play

### Step 1: Commitment Phase

Both players independently run the `commit` program:

```bash
./commit
```

When prompted, enter your choice (1 for rock, 2 for paper, 3 for scissors).
The program will output a nonce and a hash. Share only the hash with your opponent.

### Step 2: Reveal Phase

After both players have exchanged hashes, reveal your choice and nonce to each other.

### Step 3: Verification

Both players run the `verify` program to check if the opponent was honest:

```bash
./verify
```

When prompted:
1. Enter the opponent's claimed choice (1, 2, or 3).
2. Enter the opponent's nonce (copy and paste the hex values).
3. Enter the hash that the opponent originally shared (copy and paste the hex values).

The program will tell you if your opponent was trustworthy or not.

### Step 4: Determine the Winner

If both players are verified as trustworthy, determine the winner using standard Rock-Paper-Scissors rules:
- Rock (1) beats Scissors (2)
- Scissors (2) beats Paper (3)
- Paper (3) beats Rock (1)

## How It Works

This implementation uses cryptographic hash functions from the libsodium library to ensure neither player can cheat by changing their choice after seeing the opponent's selection. The random nonce prevents pre-computed hash attacks.

## License

This project is open source and available under the MIT License.
