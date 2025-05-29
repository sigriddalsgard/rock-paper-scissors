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
  printf("What did your oponent choose? (1 = rock, 2 = paper or 3 = scissor) ");
  scanf("%d", &choice);

  printf("Nonce: ");
  unsigned char nonce[NONCE_SIZE];

  for (int i = 0; i < NONCE_SIZE; i++) {
    unsigned int byte;
    scanf("%x", &byte);
    nonce[i] = byte;
  }

  printf("Hash: ");
  unsigned char expected[crypto_generichash_BYTES];

  for (int i = 0; i < crypto_generichash_BYTES; i++) {
    unsigned int byte;
    scanf("%x", &byte);
    expected[i] = byte;
  }

  unsigned char buffer[sizeof(choice) + NONCE_SIZE];
  memcpy(buffer, &choice, sizeof(choice));
  memcpy(buffer + sizeof(choice), nonce, NONCE_SIZE);

  unsigned char actual[crypto_generichash_BYTES];
  crypto_generichash(actual, sizeof(actual), buffer, sizeof(buffer), NULL, 0);

  printf("%s\n", memcmp(actual, expected, crypto_generichash_BYTES) == 0
                     ? "You have a very trustworthy opponent 🥳"
                     : "Liar, liar, pants on fire!");

  return 0;
}
