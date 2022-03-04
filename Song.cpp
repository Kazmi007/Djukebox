#include "Song.h"


Song Song::ADVERTISEMENT_SONG = Song("advertisement", 30);  // Definition of the advertisement track.

Song::Song(const std::string &name, int duration) {  // Custom constructor.
    static int songId = 1;

    this->name = name;
    this->duration = duration;
    this->songId = songId;

    songId += 1;
}

int Song::getSongId() const {  // Returns the song's ID.
    return this->songId;
}

const std::string &Song::getName() const {  // Returns the song's name.
    return this->name;
}

int Song::getDuration() const {  // Returns the duration of the song.
    return this->duration;
}

bool Song::operator==(const Song &rhs) const {  // Overloaded equality operator.
    return this->songId == rhs.songId && this->name == rhs.name && this->duration == rhs.duration;
}

bool Song::operator!=(const Song &rhs) const {  // Overloaded inequality operator.
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Song &song) {  // Overloaded operator to print song to output stream.
    os << "songId: " << song.songId << " |";
    os << " name: " << song.name << " |";
    os << " duration: " << song.duration;

    return os;
}
