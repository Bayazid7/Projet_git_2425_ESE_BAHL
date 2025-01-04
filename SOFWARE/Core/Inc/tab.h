/*
 * tab.h
 *
 *  Created on: Dec 6, 2024
 *      Author: aliou
 */

#ifndef INC_TAB_H_
#define INC_TAB_H_

#define TABLE_SIZE 457
uint8_t sendTab[TABLE_SIZE] = {
    // Message de démarrage
    0xA5, 0x5A, 0x05, 0x00, 0x00, 0x40, 0x81,

    // Paquet 1
    0x55, 0xAA, 0x00, 0x28, 0xC0, 0x00, 0x80, 0x03,
    0x10, 0x01, 0x20, 0x02, 0x30, 0x03, 0x40, 0x04,
    0x50, 0x05, 0x60, 0x06, 0x70, 0x07, 0x80, 0x08,
    0x90, 0x09, 0xA0, 0x0A, 0xB0, 0x0B, 0xC0, 0x0C,
    0xD0, 0x0D, 0xE0, 0x0E, 0xF0, 0x0F, 0x00, 0x10,
    0x10, 0x11, 0x20, 0x12, 0x30, 0x13, 0x40, 0x14,
    0x50, 0x15, 0x60, 0x16, 0x70, 0x17, 0x80, 0x18,

    // Paquet 2
    0x55, 0xAA, 0x00, 0x28, 0x40, 0x01, 0x90, 0x02,
    0x34, 0x03, 0x48, 0x04, 0x5C, 0x05, 0x70, 0x06,
    0x84, 0x07, 0x98, 0x08, 0xAC, 0x09, 0xC0, 0x0A,
    0xD4, 0x0B, 0xE8, 0x0C, 0xFC, 0x0D, 0x10, 0x0E,
    0x24, 0x0F, 0x38, 0x10, 0x4C, 0x11, 0x60, 0x12,
    0x74, 0x13, 0x88, 0x14, 0x9C, 0x15, 0xB0, 0x16,
    0xC4, 0x17, 0xD8, 0x18, 0xEC, 0x19, 0x00, 0x1A,

    // Paquet 3
    0x55, 0xAA, 0x00, 0x28, 0x80, 0x01, 0x20, 0x04,
    0x44, 0x05, 0x2C, 0x03, 0x64, 0x02, 0xDC, 0x01,
    0x18, 0x02, 0x28, 0x03, 0x38, 0x04, 0x48, 0x05,
    0x58, 0x06, 0x68, 0x07, 0x78, 0x08, 0x88, 0x09,
    0x98, 0x0A, 0xA8, 0x0B, 0xB8, 0x0C, 0xC8, 0x0D,
    0xD8, 0x0E, 0xE8, 0x0F, 0xF8, 0x10, 0x08, 0x11,
    0x18, 0x12, 0x28, 0x13, 0x38, 0x14, 0x48, 0x15,

    // Paquet 4
    0x55, 0xAA, 0x00, 0x28, 0x60, 0x01, 0x50, 0x04,
    0x18, 0x02, 0x28, 0x03, 0x38, 0x04, 0x48, 0x05,
    0x58, 0x06, 0x68, 0x07, 0x78, 0x08, 0x88, 0x09,
    0x98, 0x0A, 0xA8, 0x0B, 0xB8, 0x0C, 0xC8, 0x0D,
    0xD8, 0x0E, 0xE8, 0x0F, 0xF8, 0x10, 0x08, 0x11,
    0x18, 0x12, 0x28, 0x13, 0x38, 0x14, 0x48, 0x15,
    0x50, 0x16, 0x60, 0x17, 0x70, 0x18, 0x80, 0x19,

    // Paquet 5
    0x55, 0xAA, 0x00, 0x28, 0xF0, 0x01, 0xC8, 0x05,
    0x74, 0x03, 0xA0, 0x02, 0x88, 0x01, 0x44, 0x05,
    0x20, 0x03, 0xB8, 0x02, 0xE0, 0x01, 0x58, 0x04,
    0xA0, 0x03, 0x78, 0x02, 0xF4, 0x01, 0xC0, 0x05,
    0xA8, 0x04, 0x64, 0x02, 0x30, 0x01, 0xE8, 0x03,
    0x90, 0x02, 0xB8, 0x05, 0x70, 0x04, 0x60, 0x02,
    0xD8, 0x01, 0x88, 0x03, 0x98, 0x04, 0xB4, 0x05
};

#endif /* INC_TAB_H_ */
