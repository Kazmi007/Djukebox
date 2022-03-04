#include "Album.h"

Album::Album(const std::string &name) {  // Custom constructor.
    static int albumId = 1;

    this->name = name;
    this->albumId = albumId;

    albumId += 1;
}

int Album::getAlbumId() const {  // Returns the album ID.
    return this->albumId;
}

const std::string &Album::getName() const {  // Returns the album name.
    return this->name;
}

const LinkedList<Song *> &Album::getSongs() const {  // Returns the song list for the album.
    return this->songs;
}

void Album::addSong(Song *song) {  // Adds given song to the end of the album song list. 
    this->songs.insertAtTheEnd(song);
}

void Album::dropSong(Song *song) {  // Removes given song from the album song list.
    this->songs.removeNode(song);
}

bool Album::operator==(const Album &rhs) const {  // Overloaded equality operator.
    return this->albumId == rhs.albumId && this->name == rhs.name;
}

bool Album::operator!=(const Album &rhs) const {  // Overloaded inequality operator.
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Album &album) {  // Overloaded operator to print album to output stream.
    os << "aldumId: " << album.albumId << " |";
    os << " name: " << album.name << " |";

    os << " songs: [";
    Node<Song *> *firstSongNode = album.songs.getFirstNode();
    Node<Song *> *songNode = firstSongNode;
    if (songNode) {
        do {
            os << *(songNode->data);
            if (songNode->next != firstSongNode) os << ", ";
            songNode = songNode->next;
        } while (songNode != firstSongNode);
    }
    os << "]";

    return os;
}
