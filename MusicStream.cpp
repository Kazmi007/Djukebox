#include "MusicStream.h"

#include <iostream>

void MusicStream::addProfile(const std::string &email, const std::string &username, SubscriptionPlan plan) {  // Adds a new profile to the platform.
    Profile p(email, username, plan);
    this->profiles.insertAtTheEnd(p);
}

void MusicStream::deleteProfile(const std::string &email) {  // Deletes given profile from the platform.
    Node<Profile> *curr, *head = (this->profiles).getFirstNode();
    int flag = 1;
    curr = head;
    while (flag || curr != head) {
        if (curr->data.getEmail() == email) {
            Profile *p = &(curr->data);
            Node<Profile *> *next, *curr1, *head1 = p->getFollowings().getFirstNode();
            std::cout << head1 << std::endl;
            if (head1) {
                curr1 = head1;
                while (curr1 != curr1->next) {
                    next = curr1->next;
                    p->unfollowProfile(curr1->data);
                    curr1 = next;
                }
                p->unfollowProfile(curr1->data);
            }
            head1 = p->getFollowers().getFirstNode();
            if (head1) {
                curr1 = head1;
                while (curr1 != curr1->next) {
                    next = curr1->next;
                    (curr1->data)->unfollowProfile(p);
                    curr1 = next;
                }
                (curr1->data)->unfollowProfile(p);
            }
            ((curr->data).getPlaylists()).~LinkedList();
            ((curr->data).getFollowings()).~LinkedList();
            ((curr->data).getFollowers()).~LinkedList();
            this->profiles.removeNode(curr);
            return;
        }
        flag = 0;
        curr = curr->next;
    }
}

void MusicStream::addArtist(const std::string &artistName) {  // Adds a new artist to the platform.
    Artist ar(artistName);
    this->artists.insertAtTheEnd(ar);
}

void MusicStream::addAlbum(const std::string &albumName, int artistId) {  // Adds a new album to the platform. 
    Album al(albumName); 
    this->albums.insertAtTheEnd(al);
    Node<Artist> *curr, *head = (this->artists).getFirstNode();
    int flag = 1;
    curr = head;
    while (flag || curr != head) {
        if ((curr->data).getArtistId() == artistId) {
            (curr->data).addAlbum(&(this->albums.getLastNode()->data));
            return;
        }
        flag = 0;
        curr = curr->next;
    }
}

void MusicStream::addSong(const std::string &songName, int songDuration, int albumId) {  // Adds a new song to the platform.
    Song sn(songName, songDuration);
    this->songs.insertAtTheEnd(sn);
    Node<Album> *curr, *head = (this->albums).getFirstNode();
    int flag = 1;
    curr = head;
    while (flag || curr != head) {
        if ((curr->data).getAlbumId() == albumId) {
            (curr->data).addSong(&(this->songs.getLastNode()->data));
            return;
        }
        flag = 0;
        curr = curr->next;
    }
}

void MusicStream::followProfile(const std::string &email1, const std::string &email2) {  // Makes profile1 follow profile2.
    Node<Profile> *curr, *head = (this->profiles).getFirstNode();
    Profile *p1, *p2;
    int flag = 1;
    curr = head;
    while (flag || curr != head) {
        if (curr->data.getEmail() == email1) {
            p1 = &(curr->data);
            break;
        }
        flag = 0;
        curr = curr->next;
    }
    flag = 1;
    curr = head;
    while (flag || curr != head) {
        if (curr->data.getEmail() == email2) {
            p2 = &(curr->data);
            break;
        }
        flag = 0;
        curr = curr->next;
    }
    p1->followProfile(p2);
}

void MusicStream::unfollowProfile(const std::string &email1, const std::string &email2) {  // Makes profile1 unfollow profile2.
    Node<Profile> *curr, *head = (this->profiles).getFirstNode();
    Profile *p1, *p2;
    int flag = 1;
    curr = head;
    while (flag || curr != head) {
        if (curr->data.getEmail() == email1) {
            p1 = &(curr->data);
            break;
        }
        flag = 0;
        curr = curr->next;
    }
    flag = 1;
    curr = head;
    while (flag || curr != head) {
        if (curr->data.getEmail() == email2) {
            p2 = &(curr->data);
            break;
        }
        flag = 0;
        curr = curr->next;
    }
    p1->unfollowProfile(p2);
}

void MusicStream::createPlaylist(const std::string &email, const std::string &playlistName) {  // Creates a new playlist for the given profile.
    Node<Profile> *curr, *head = (this->profiles).getFirstNode();
    Profile *p;
    int flag = 1;
    curr = head;
    while (flag || curr != head) {
        if (curr->data.getEmail() == email) {
            p = &(curr->data);
            break;
        }
        flag = 0;
        curr = curr->next;
    }
    p->createPlaylist(playlistName);
}

void MusicStream::deletePlaylist(const std::string &email, int playlistId) {  // Deletes a given a playlist for a given profile.
    Node<Profile> *curr, *head = (this->profiles).getFirstNode();
    Profile *p;
    int flag = 1;
    curr = head;
    while (flag || curr != head) {
        if (curr->data.getEmail() == email) {
            p = &(curr->data);
            break;
        }
        flag = 0;
        curr = curr->next;
    }
    p->deletePlaylist(playlistId);
}

void MusicStream::addSongToPlaylist(const std::string &email, int songId, int playlistId) {  // Adds a new song to the given playlist of the given profile.
    Node<Profile> *curr, *head = (this->profiles).getFirstNode();
    Profile *p;
    int flag = 1;
    curr = head;
    while (flag || curr != head) {
        if (curr->data.getEmail() == email) {
            p = &(curr->data);
            break;
        }
        flag = 0;
        curr = curr->next;
    }
    Playlist *pl = p->getPlaylist(playlistId);
    Node<Song> *curr1, *head1 = (this->songs).getFirstNode();
    Song *s;
    flag = 1;
    curr1 = head1;
    while (flag || curr1 != head1) {
        if (curr1->data.getSongId()== songId) {
            s = &(curr1->data);
            break;
        }
        flag = 0;
        curr1 = curr1->next;
    }
    pl->addSong(s);
}

void MusicStream::deleteSongFromPlaylist(const std::string &email, int songId, int playlistId) {  // Removes a given song from a given playlist for a given profile.
    Node<Profile> *curr, *head = (this->profiles).getFirstNode();
    Profile *p;
    int flag = 1;
    curr = head;
    while (flag || curr != head) {
        if (curr->data.getEmail() == email) {
            p = &(curr->data);
            break;
        }
        flag = 0;
        curr = curr->next;
    }
    Playlist *pl = p->getPlaylist(playlistId);
    Node<Song> *curr1, *head1 = (this->songs).getFirstNode();
    Song *s;
    flag = 1;
    curr1 = head1;
    while (flag || curr1 != head1) {
        if (curr1->data.getSongId()== songId) {
            s = &(curr1->data);
            break;
        }
        flag = 0;
        curr1 = curr1->next;
    }
    pl->dropSong(s);
}

LinkedList<Song *> MusicStream::playPlaylist(const std::string &email, Playlist *playlist) {  // Plays the given playlist for the given profile.
    Node<Profile> *curr, *head = (this->profiles).getFirstNode();
    Profile *p;
    int flag = 1;
    curr = head;
    while (flag || curr != head) {
        if (curr->data.getEmail() == email) {
            p = &(curr->data);
            break;
        }
        flag = 0;
        curr = curr->next;
    }
    LinkedList<Song *> sn = playlist->getSongs();
    Song s;
    if (p->getPlan() != premium) {
        sn.insertAsEveryKthNode(&(s.ADVERTISEMENT_SONG), 2);  // Advertisement for non-premium profiles.
    }
    return sn;
}

Playlist *MusicStream::getPlaylist(const std::string &email, int playlistId) {  // Returns playlist with given ID for a given profile.
    Node<Profile> *curr, *head = (this->profiles).getFirstNode();
    Profile *p;
    int flag = 1;
    curr = head;
    while (flag || curr != head) {
        if (curr->data.getEmail() == email) {
            p = &(curr->data);
            break;
        }
        flag = 0;
        curr = curr->next;
    }
    return p->getPlaylist(playlistId);
}

LinkedList<Playlist *> MusicStream::getSharedPlaylists(const std::string &email) {  // Returns shared playlists of the profiles followed by the given profile.
    Node<Profile> *curr, *head = (this->profiles).getFirstNode();
    Profile *p;
    int flag = 1;
    curr = head;
    while (flag || curr != head) {
        if (curr->data.getEmail() == email) {
            p = &(curr->data);
            break;
        }
        flag = 0;
        curr = curr->next;
    }
    LinkedList<Playlist *> list;
    Node<Profile *> *curr1, *head1 = (p->getFollowings()).getFirstNode();
    if (head1) {
        flag = 1;
        curr1 = head1;
        while (flag || curr1 != head1) {
            Node<Playlist> *curr2, *head2 = (curr1->data->getPlaylists()).getFirstNode();
            if (head2) {
                int flag1 = 1;
                curr2 = head2;
                while (flag1 || curr2 != head2) {
                    if (curr2->data.isShared())
                        list.insertAtTheEnd(&(curr2->data));
                    flag1 = 0;
                    curr2 = curr2->next;
                }
            }
            flag = 0;
            curr1 = curr1->next;
        }
    }
    return list;
}

void MusicStream::shufflePlaylist(const std::string &email, int playlistId, int seed) {  // Shuffles the given playlist with a given seed for a given profile.
    Node<Profile> *curr, *head = (this->profiles).getFirstNode();
    Profile *p;
    int flag = 1;
    curr = head;
    while (flag || curr != head) {
        if (curr->data.getEmail() == email) {
            p = &(curr->data);
            break;
        }
        flag = 0;
        curr = curr->next;
    }
    Playlist *pl = p->getPlaylist(playlistId);
    (pl->getSongs()).shuffle(seed);
}

void MusicStream::sharePlaylist(const std::string &email, int playlistId) {  // Shares the given playlist for the given user.
    Node<Profile> *curr, *head = (this->profiles).getFirstNode();
    Profile *p;
    int flag = 1;
    curr = head;
    while (flag || curr != head) {
        if (curr->data.getEmail() == email) {
            p = &(curr->data);
            break;
        }
        flag = 0;
        curr = curr->next;
    }
    Playlist *pl = p->getPlaylist(playlistId);
    pl->setShared(true);
}

void MusicStream::unsharePlaylist(const std::string &email, int playlistId) {  // Unshares the given playlist for the given user.
    Node<Profile> *curr, *head = (this->profiles).getFirstNode();
    Profile *p;
    int flag = 1;
    curr = head;
    while (flag || curr != head) {
        if (curr->data.getEmail() == email) {
            p = &(curr->data);
            break;
        }
        flag = 0;
        curr = curr->next;
    }
    Playlist *pl = p->getPlaylist(playlistId);
    pl->setShared(false);
}

void MusicStream::subscribePremium(const std::string &email) {  // Sets the subscription plan of the given profile to premium.
    Node<Profile> *curr, *head = (this->profiles).getFirstNode();
    Profile *p;
    int flag = 1;
    curr = head;
    while (flag || curr != head) {
        if (curr->data.getEmail() == email) {
            p = &(curr->data);
            break;
        }
        flag = 0;
        curr = curr->next;
    }
    p->setPlan(premium);
}

void MusicStream::unsubscribePremium(const std::string &email) {  // Sets the subscription plan of the given profile to free.
    Node<Profile> *curr, *head = (this->profiles).getFirstNode();
    Profile *p;
    int flag = 1;
    curr = head;
    while (flag || curr != head) {
        if (curr->data.getEmail() == email) {
            p = &(curr->data);
            break;
        }
        flag = 0;
        curr = curr->next;
    }
    p->setPlan(free_of_charge);
}

void MusicStream::print() const {  // Prints the platform data.
    std::cout << "# Printing the music stream ..." << std::endl;

    std::cout << "# Number of profiles is " << this->profiles.getSize() << ":" << std::endl;
    this->profiles.print();

    std::cout << "# Number of artists is " << this->artists.getSize() << ":" << std::endl;
    this->artists.print();

    std::cout << "# Number of albums is " << this->albums.getSize() << ":" << std::endl;
    this->albums.print();

    std::cout << "# Number of songs is " << this->songs.getSize() << ":" << std::endl;
    this->songs.print();

    std::cout << "# Printing is done." << std::endl;
}
