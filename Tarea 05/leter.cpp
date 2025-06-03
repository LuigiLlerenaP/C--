#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_SONGS = 20;
const int MAX_LINES = 20;

string titles[MAX_SONGS];
string lyrics[MAX_SONGS][MAX_LINES];

bool startsWith(const string &line, const string &prefix)
{
    return line.rfind(prefix, 0) == 0;
}

string extractContent(const string &line, const string &prefix)
{
    return line.substr(prefix.size());
}

struct Line
{
    string text;
    Line *next;
};

struct Song
{
    string title;
    Line *firstLine;
    Song *nextSong;
};

// Crear línea
Line *createLine(const string &text)
{
    Line *newLine = new Line;
    newLine->text = text;
    newLine->next = nullptr;
    return newLine;
}

// Crear canción vacía
Song *createSong(const string &title)
{
    Song *newSong = new Song;
    newSong->title = title;
    newSong->firstLine = nullptr;
    newSong->nextSong = nullptr;
    return newSong;
}

// Agregar nueva canción a la lista, devuelve el puntero a la nueva canción
Song *addNewSong(Song *&firstSong, Song *&lastSong, const string &title)
{
    Song *newSong = createSong(title);
    if (!firstSong)
    {
        firstSong = newSong;
    }
    else
    {
        lastSong->nextSong = newSong;
    }
    lastSong = newSong;
    return newSong;
}

// Agregar línea a la canción, actualiza el puntero lastLine
void addLineToSong(Song *song, Line *&lastLine, const string &text)
{
    Line *newLine = createLine(text);
    if (song->firstLine == nullptr)
    {
        song->firstLine = newLine;
    }
    else
    {
        lastLine->next = newLine;
    }
    lastLine = newLine;
}

// Leer canciones del archivo y guardar en arreglos
int loadSongsToArrays(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "No se pudo abrir el archivo: " << filename << endl;
        return 0;
    }

    int currentSongIndex = -1;
    int currentLineIndex = 0;
    string line;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        if (startsWith(line, "Cancion :"))
        {
            currentSongIndex++;
            if (currentSongIndex >= MAX_SONGS)
            {
                cerr << "Se alcanzó el límite máximo de canciones (" << MAX_SONGS << ")" << endl;
                break;
            }
            titles[currentSongIndex] = extractContent(line, "Cancion :");
            currentLineIndex = 0;
        }
        else if (startsWith(line, "Letra :"))
        {
            if (currentSongIndex < 0)
                continue; // No hay canción actual
            if (currentLineIndex >= MAX_LINES)
                continue; // Evitar overflow de líneas
            lyrics[currentSongIndex][currentLineIndex++] = extractContent(line, "Letra :");
        }
        else
        {
            if (currentSongIndex < 0 || currentLineIndex >= MAX_LINES)
                continue;
            lyrics[currentSongIndex][currentLineIndex++] = line;
        }
    }

    file.close();
    return currentSongIndex + 1; // Número de canciones leídas
}

// Crear lista enlazada a partir de los arreglos
Song *createSongListFromArrays(int songCount)
{
    Song *firstSong = nullptr;
    Song *lastSong = nullptr;

    for (int i = 0; i < songCount; i++)
    {
        Song *newSong = addNewSong(firstSong, lastSong, titles[i]);
        Line *lastLine = nullptr;

        for (int j = 0; j < MAX_LINES; j++)
        {
            if (lyrics[i][j].empty())
                break;
            addLineToSong(newSong, lastLine, lyrics[i][j]);
        }
    }
    return firstSong;
}

// Mostrar canciones
void printSongs(Song *head)
{
    Song *current = head;
    while (current != nullptr)
    {
        cout << "Canción: " << current->title << endl;
        Line *l = current->firstLine;
        while (l != nullptr)
        {
            cout << "  " << l->text << endl;
            l = l->next;
        }
        cout << endl;
        current = current->nextSong;
    }
}

int main()
{
    int songCount = loadSongsToArrays("canciones.txt");
    if (songCount > 0)
    {
        Song *songList = createSongListFromArrays(songCount);
        printSongs(songList);
    }
    return 0;
}
