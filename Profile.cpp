#include "Profile.h"

Profile::Profile(const std::string &email, const std::string &username, SubscriptionPlan plan) {  // Custom constructor.
    this->email = email;
    this->username = username;
    this->plan = plan;
}

const std::string &Profile::getUsername() const {  // Returns profile username.
    return this->username;
}

const std::string &Profile::getEmail() const {  // Returns profile email.
    return this->email;
}

SubscriptionPlan Profile::getPlan() const {  // Returns the subscription plan of the profile.
    return this->plan;
}

LinkedList<Playlist> &Profile::getPlaylists() {  // Returns the profile playlists.
    return this->playlists;
}

LinkedList<Profile *> &Profile::getFollowings() {  // Returns the profile following.
    return this->following;
}

LinkedList<Profile *> &Profile::getFollowers() {  // Returns the profile followers.
    return this->followers;
}

void Profile::setPlan(SubscriptionPlan plan) {  // Sets the subscription plan for the profile.
    this->plan = plan;
}

void Profile::followProfile(Profile *profile) {  // Makes the profile follow a given profile.
    this->following.insertAtTheEnd(profile);
    profile->followers.insertAtTheEnd(this);
}

void Profile::unfollowProfile(Profile *profile) {  // Makes the profile unfollow a given profile
    this->following.removeNode(profile);
    profile->followers.removeNode(this);
}

void Profile::createPlaylist(const std::string &playlistName) {  // Creates a new playlist for the profile.
    Playlist p(playlistName);    
    this->playlists.insertAtTheEnd(p);
 }

void Profile::deletePlaylist(int playlistId) {
    Node<Playlist> *curr, *head = (this->playlists).getFirstNode();  // Deletes the given playlist.
    if ((head->data).getPlaylistId() == playlistId) {
        this->playlists.removeNode(head);
        return;
    }
    curr = head->next;
    while (curr != head) {
        if ((curr->data).getPlaylistId() == playlistId) {
            this->playlists.removeNode(curr);
            return;
        }
        curr = curr->next;
    }
}

void Profile::addSongToPlaylist(Song *song, int playlistId) {  // Adds given song to the given playlist.
    Node<Playlist> *curr, *head = (this->playlists).getFirstNode();
    if ((head->data).getPlaylistId() == playlistId) {
       (head->data).addSong(song);
        return;
    }
    curr = head->next;
    while (curr != head) {
        if ((curr->data).getPlaylistId() == playlistId) {
            (curr->data).addSong(song);
            return;
        }
        curr = curr->next;
    }
}

void Profile::deleteSongFromPlaylist(Song *song, int playlistId) {  // Deletes given song from the given playlist.
    Node<Playlist> *curr, *head = (this->playlists).getFirstNode();
    if ((head->data).getPlaylistId() == playlistId) {
        (head->data).dropSong(song);
        return;
    }
    curr = head->next;
    while (curr != head) {
        if ((curr->data).getPlaylistId() == playlistId) {
            (curr->data).dropSong(song);
            return;
        }
        curr = curr->next;
    }
}

Playlist *Profile::getPlaylist(int playlistId) {  // Returns required playlist.
    Node<Playlist> *curr, *head = (this->playlists).getFirstNode();
    curr = head->next;
    while (curr != head) {
        if ((curr->data).getPlaylistId() == playlistId) 
            return &(curr->data);
        curr = curr->next;
    }
    return &(head->data);
}

LinkedList<Playlist *> Profile::getSharedPlaylists() {  // Returns a list of shared playlists.
    LinkedList<Playlist *> list;
    Node<Profile *> *curr, *head = (this->following).getFirstNode();
    int flag = 1;
    curr = head;
    while (flag || curr != head) {
        Node<Playlist> *curr1, *head1 = ((curr->data)->playlists).getFirstNode();
        int flag1 = 1;
        curr1 = head1;
        while (flag1 || curr1 != head1) {
            if ((curr1->data).isShared()) 
                list.insertAtTheEnd(&(curr1->data));
        }
        flag = 0;
        curr = curr->next;
    }
    return list;
}

void Profile::shufflePlaylist(int playlistId, int seed) {  // Shuffles the playlist with a given seed.
    Node<Playlist> *curr, *head = (this->playlists).getFirstNode();
    if ((head->data).getPlaylistId() == playlistId){ 
        (head->data).shuffle(seed);
        return;
    }
    curr = head->next;
    while (curr != head) {
        if ((curr->data).getPlaylistId() == playlistId){ 
            (curr->data).shuffle(seed);
            return;
        }
        curr = curr->next;
    }
}

void Profile::sharePlaylist(int playlistId) {
    Node<Playlist> *curr, *head = (this->playlists).getFirstNode();
    if ((head->data).getPlaylistId() == playlistId){ 
        (head->data).setShared(true);
        return;
    }
    curr = head->next;
    while (curr != head) {
        if ((curr->data).getPlaylistId() == playlistId){ 
            (curr->data).setShared(true);
            return;
        }
        curr = curr->next;
    }
}

void Profile::unsharePlaylist(int playlistId) {  // Unshares a given a playlist.
    Node<Playlist> *curr, *head = (this->playlists).getFirstNode(); 
    if ((head->data).getPlaylistId() == playlistId){ 
        (head->data).setShared(false);
        return;
    }
    curr = head->next;
    while (curr != head) {
        if ((curr->data).getPlaylistId() == playlistId){ 
            (curr->data).setShared(false);
            return;
        }
        curr = curr->next;
    }
}

bool Profile::operator==(const Profile &rhs) const {  // Overloaded equality operator.
    return this->email == rhs.email && this->username == rhs.username && this->plan == rhs.plan;
}

bool Profile::operator!=(const Profile &rhs) const {  // Overloaded inequality operator.
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Profile &profile) {  // Overloaded operator to profile to output stream.
    os << "email: " << profile.email << " |";
    os << " username: " << profile.username << " |";
    if (profile.plan == free_of_charge) {
        os << " plan: " << "free_of_charge" << " |";
    } else if (profile.plan == premium) {
        os << " plan: " << "premium" << " |";
    } else {
        os << " plan: " << "undefined" << " |";
    }

    os << " playlists: [";
    Node<Playlist> *firstPlaylistNode = profile.playlists.getFirstNode();
    Node<Playlist> *playlistNode = firstPlaylistNode;
    if (playlistNode) {
        do {
            os << playlistNode->data;
            if (playlistNode->next != firstPlaylistNode) os << ", ";
            playlistNode = playlistNode->next;
        } while (playlistNode != firstPlaylistNode);
    }
    os << "] |";
    os << " following: [";
    Node<Profile *> *firstProfileNode = profile.following.getFirstNode();
    Node<Profile *> *profileNode = firstProfileNode;
    if (profileNode) {
        do {
            os << profileNode->data->getEmail();
            if (profileNode->next != firstProfileNode) os << ", ";
            profileNode = profileNode->next;
        } while (profileNode != firstProfileNode);
    }
    os << "] |";
    os << " followers: [";
    firstProfileNode = profile.followers.getFirstNode();
    profileNode = firstProfileNode;
    if (profileNode) {
        do {
            os << profileNode->data->getEmail();
            if (profileNode->next != firstProfileNode) os << ", ";
            profileNode = profileNode->next;
        } while (profileNode != firstProfileNode);
    }
    os << "]";

    return os;
}
