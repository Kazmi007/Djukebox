#include "Playlist.h"

Playlist::Playlist(const std::string &name) {  // Custom consructor.
    static int playlistId = 1;

    this->name = name;
    this->shared = false;
    this->playlistId = playlistId;

    playlistId += 1;
}

int Playlist::getPlaylistId() const {  // Returns playlist ID.
    return this->playlistId;
}

const std::string &Playlist::getName() const {  // Returns playlist name.
    return this->name;
}

bool Playlist::isShared() const {  // Returns whether the playlist is shared or not.
    return this->shared;
}

LinkedList<Song *> &Playlist::getSongs() {  // Returns the list of songs.
    return this->songs;
}

void Playlist::setShared(bool shared) {  // Sets whether the playlist is shared.
    this->shared = shared;
}

void Playlist::addSong(Song *song) {  // Adds song to the end of the playlist
    this->songs.insertAtTheEnd(song);
}

void Playlist::dropSong(Song *song) {  // Removes given song from the playlist.
    this->songs.removeNode(song);
}

void Playlist::shuffle(int seed) {  // Shuffles the songs in the playlist with a given seed.
    this->songs.shuffle(seed);
}

bool Playlist::operator==(const Playlist &rhs) const {  // Overloaded equality operator.
    return this->playlistId == rhs.playlistId && this->name == rhs.name && this->shared == rhs.shared;
}

bool Playlist::operator!=(const Playlist &rhs) const {  // Overloaded inequality operator.
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Playlist &playlist) {  // Overloaded operator to print playlist to output stream.
    os << "playlistId: " << playlist.playlistId << " |";
    os << " name: " << playlist.name << " |";
    os << " shared: " << (playlist.shared ? "yes" : "no") << " |";

    os << " songs: [";
    Node<Song *> *firstSongNode = playlist.songs.getFirstNode();
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
