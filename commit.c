#include <sodium.h>
#include <stdio.h>
#include <string.h>

#define ROCK 1
#define SCISSORS 2
#define PAPER 3

#define NONCE_SIZE 16

int main() {
  if (sodium_init() < 0)
    return 1;

  int choice;
  printf("Choose 1 = rock, 2 = paper or 3 = scissor: ");
  scanf("%d", &choice);

  unsigned char nonce[NONCE_SIZE];
  randombytes_buf(nonce, sizeof(nonce));

  printf("Nonce: ");
  for (int i = 0; i < NONCE_SIZE; i++) {
    printf("%02x ", nonce[i]);
  }
  printf("\n");

  unsigned char buffer[sizeof(choice) + NONCE_SIZE];
  memcpy(buffer, &choice, sizeof(choice));
  memcpy(buffer + sizeof(choice), nonce, NONCE_SIZE);

  unsigned char hash[crypto_generichash_BYTES];
  crypto_generichash(hash, sizeof(hash), buffer, sizeof(buffer), NULL, 0);

  printf("Hash: ");
  for (int i = 0; i < crypto_generichash_BYTES; i++) {
    printf("%02x ", hash[i]);
  }
  printf("\n");

  return 0;
}
