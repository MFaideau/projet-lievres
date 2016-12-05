#include "Trame.h"

unsigned short crc16(byte byteArray[], int length)
{
    unsigned char x;
    unsigned short crc = 0xFFFF;
    for (int i = 0; i < length; i++) {
        x = crc >> 8 ^ byteArray[i];
        x ^= x >> 4;
        crc = (crc << 8) ^ ((unsigned short)(x << 12)) ^ ((unsigned short)(x << 5)) ^ ((unsigned short)x);
    }
    return crc;
}

void float2Bytes(float val, byte* bytes_array)
{
    union {
        float float_variable;
        byte temp_array[4];
    } u;
    u.float_variable = val;
    memcpy(bytes_array, u.temp_array, 4);
}

    Position::Position(bool north, bool south, bool east, bool west, short degLon, short degLat, float minutesLong, float minutesLat, float secondesLong, float secondesLat) {
        this->north = north;
        this->south = south;
        this->east = east;
        this->west = west;
        this->degLon = degLon;
        this->degLat = degLat;
        this->minutesLong = minutesLong;
        this->minutesLat = minutesLat;
        this->secondesLong = secondesLong;
        this->secondesLat = secondesLat;
    }

    Position::Position(byte* posBytes) {
        this->north = (posBytes[0] & 1);
        this->south = (posBytes[0] & 2) >> 1;
        this->east = (posBytes[0] & 4) >> 2;
        this->west = (posBytes[0] & 8) >> 3;
        this->degLon = posBytes[1] * 256 + posBytes[2];
        this->degLat = posBytes[3] * 256 + posBytes[4];
        this->minutesLong = *(float *)(posBytes + 5);
        this->minutesLat = *(float *)(posBytes + 9);
        this->secondesLong = *(float *)(posBytes + 13);
        this->secondesLat = *(float *)(posBytes + 17);
    }

    byte* Position::GetBytes() {
        byte* posByte = (byte*)malloc(21 * sizeof(byte));
        posByte[0] = 0;
        if (this->north) {
            posByte[0] = posByte[0] | 1;
        }
        if (this->south) {
            posByte[0] = posByte[0] | 2;
        }
        if (this->east) {
            posByte[0] = posByte[0] | 4;
        }
        if (this->west) {
            posByte[0] = posByte[0] | 8;
        }
        posByte[1] = (this->degLon & 0xFF00) >> 8; //Bits de poids fort du short
        posByte[2] = (this->degLon & 0x00FF); //Bits de poids faible
        posByte[3] = (this->degLat & 0xFF00) >> 8; //Bits de poids fort du short
        posByte[4] = (this->degLat & 0x00FF); //Bits de poids faible
        float2Bytes(this->minutesLong, posByte + 5);
        float2Bytes(this->minutesLat, posByte + 9);
        float2Bytes(this->secondesLong, posByte + 13);
        float2Bytes(this->secondesLat, posByte + 17);
        return posByte;
    }

    byte* Date::GetBytes() {
        byte* dateByte = (byte*)malloc(6 * sizeof(byte));
        dateByte[0] = this->jour;
        dateByte[1] = this->mois;
        dateByte[2] = this->annee;
        dateByte[3] = this->heure;
        dateByte[4] = this->minutes;
        dateByte[5] = this->secondes;
        return dateByte;
    }

    Date::Date(byte jour, byte mois, byte annee, byte heure, byte minutes, byte secondes) {
        this->jour = jour;
        this->mois = mois;
        this->annee = annee;
        this->heure = heure;
        this->minutes = minutes;
        this->secondes = secondes;
    }

    Date::Date(byte* dateBytes) {
        this->jour = dateBytes[0];
        this->mois = dateBytes[1];
        this->annee = dateBytes[2];
        this->heure = dateBytes[3];
        this->minutes = dateBytes[4];
        this->secondes = dateBytes[5];
    }

    byte* Content::GetBytes() {
        byte* contByte = (byte*)malloc(29 * sizeof(byte));
        contByte[0] = (this->IDLapin & 0xFF00) << 8;
        contByte[1] = (this->IDLapin & 0x00FF);
        byte* dateBytes = this->dateLapin->GetBytes();
        byte* positionBytes = this->positionLapin->GetBytes();
        memcpy(contByte + 2, dateBytes, 6);
        memcpy(contByte + 8, positionBytes, 21);
        free(positionBytes);
        free(dateBytes);
        return contByte;
    }

    Content::Content(short IDLapin, Position* positionLapin, Date* dateLapin) {
        this->IDLapin = IDLapin;
        this->positionLapin = positionLapin;
        this->dateLapin = dateLapin;
    }

    Content::Content(byte* contentBytes) {
        this->IDLapin = contentBytes[0] * 256 + contentBytes[1];
        byte* positionBytes = (byte*)malloc(21 * sizeof(byte));
        byte* dateBytes = (byte*)malloc(6 * sizeof(byte));
        memcpy(dateBytes, contentBytes + 2, 6);
        memcpy(positionBytes, contentBytes + 8, 21);
        this->positionLapin = (Position*)(new Position(positionBytes));
        this->dateLapin =  (Date*)(new Date(dateBytes));
        free(dateBytes);
        free(positionBytes);
    }

byte* CreateMessageBytes(Content* messageContent)
{
    byte* messByte = (byte*)malloc(32 * sizeof(byte));
    messByte[0] = 20;
    byte* contentBytes = messageContent->GetBytes();
    unsigned short gotHash = crc16(contentBytes, 29);
    messByte[1] = (gotHash & 0xFF00) >> 8;
    messByte[2] = (gotHash & 0x00FF);
    memcpy(messByte + 3, contentBytes, 29);
    free(contentBytes);
    return messByte;
}
