#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef unsigned char byte;

unsigned short crc16(byte byteArray[], int length);
void float2Bytes(float val, byte* bytes_array);


class Position
{
public:
    bool north;
    bool south;
    bool east;
    bool west;
    short degLon;
    short degLat;
    float minutesLong;
    float minutesLat;
    float secondesLong;
    float secondesLat;

    Position(bool north, bool south, bool east, bool west, short degLon, short degLat, float minutesLong, float minutesLat, float secondesLong, float secondesLat);

    Position(byte* posBytes);

    byte* GetBytes();
};
class Date
{
public:
    byte jour;
    byte mois;
    byte annee;
    byte heure;
    byte minutes;
    byte secondes;

    byte* GetBytes();

    Date(byte jour, byte mois, byte annee, byte heure, byte minutes, byte secondes);

    Date(byte* dateBytes);
};

class Content
{
public:
    short IDLapin;
    Position* positionLapin;
    Date* dateLapin;

    byte* GetBytes();

    Content(short IDLapin, Position* positionLapin, Date* dateLapin);

    Content(byte* contentBytes);
};

byte* CreateMessageBytes(Content* messageContent);

enum MessageCheckResult { CORRECT = 1, CORRUPTED = 0, NOTFORUS = -1 };
MessageCheckResult IsCorrectMessage(byte* bytesReceived, int mLength);
