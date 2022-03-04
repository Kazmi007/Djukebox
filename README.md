# Music-Streaming-Platform
This project centers around making a music streaming platform using a circular linked list implementation. The principles of OOP and abstraction are highly utilized.

All the main functions and their functionalities are explained below.

Since this is supposed to be a prototype, certain assumptions (detailed below) were made.



**--Linked List Implementation:**

The linked list data structure used in this project is implemented as the class template LinkedList with the template
argument T, which is used as the type of data stored in the nodes. The node of the linked list is implemented as the class
template Node with the template argument T, which is the type of data stored in nodes. Node class is the basic building
block of the LinkedList class. LinkedList class has a single Node pointer in its private data field (namely head) which
points to the first node of the linked list, and an integer (namely size) which keeps the number of nodes in the list.

The LinkedList class has its definition and implementation in LinkedList.h file, and the Node class has its in Node.h file.


1.1 Node
Node class represents nodes that constitute linked lists. A Node instance keeps two pointers (namely prev and next) to
its previous and next nodes in the list, and a data variable of type T (namely data) to hold the data. The class has two
constructors and the overloaded output operator (operator<<).


2.2 LinkedList
LinkedList class implements a circular doubly linked list data structure. The utility functions are discussed in the following subsections.

2.2.1 LinkedList();
This is the default constructor. Necessary initializations are made here.

2.2.2 LinkedList(const LinkedList<T> &obj);
This is the copy constructor. Necessary initializations are made here, creating new nodes by copying the nodes in the
given obj, and inserting those new nodes into the linked list.

2.2.3 ∼LinkedList();
This is the destructor. Deallocates all the memory that you was allocated before.

2.2.4 int getSize() const;
This function returns an integer that is the number of nodes in the linked list (i.e., the size of the linked list).

2.2.5 bool isEmpty() const;
This function returns true if the linked list is empty (i.e., there exists no nodes in the linked list). If the linked
list is not empty, it returns false.

2.2.6 bool contains(Node<T> *node) const;
This function returns true if the linked list contains the given node (i.e., any prev/next in the nodes of the linked
list matches with node). Otherwise, it returns false.

2.2.7 Node<T> *getFirstNode() const;
This function returns a pointer to the first node in the linked list. If the linked list is empty, it returns NULL.

2.2.8 Node<T> *getLastNode() const;
This function returns a pointer to the last node in the linked list. If the linked list is empty, it returns NULL.

2.2.9 Node<T> *getNode(const T &data) const;
Searches the linked list for the node that has the same data with the given data and returns a pointer to that
node. If there exists multiple such nodes in the linked list, returns a pointer to the first occurrence. If there exists no such node in the linked list, returns NULL.

2.2.10 Node<T> *getNodeAtIndex(int index) const;
Searches the linked list for the node at the given zero-based index (i.e., index=0 means the first node, index=1
means the second node, ..., index=size-1 means the last node) and returns a pointer to that node. If there exists no
such node in the linked list (i.e., index is out of bounds), returns NULL.

2.2.11 void insertAtTheFront(const T &data);
\Creates a new node with the given data and inserts it at the front of the linked list as the first node. 

2.2.12 void insertAtTheEnd(const T &data);
Creates a new node with the given data and insert it at the end of the linked list as the last node.

2.2.13 void insertAfterNode(const T &data, Node<T> *node);
Creates a new node with the given data and insert it after the given node as its next node. If the given node is not in the linked list, does nothing.

2.2.14 void insertAsEveryKthNode(const T &data, int k);
Creates new nodes with the given data and inserts them at the linked list at every kth position. If the given
k is smaller than 2, does nothing.

2.2.15 void removeNode(Node<T> *node);
Removes the given node from the linked list. If the given node is not in the linked list, it does nothing.

2.2.16 void removeNode(const T &data);
Removes the node that has the same data with the given data from the linked list. If there exists multiple such nodes in the linked list, removes all
occurrences. If there exists no such node in the linked list, does nothing.

2.2.17 void removeAllNodes();
Removes all nodes in the linked list so that the linked list becomes empty.

2.2.18 void removeEveryKthNode(int k);
Removes every kth node from the linked list. If the given k is smaller than 2, does nothing.

2.2.19 void swap(Node<T> *node1, Node<T> *node2);
Swaps the two given nodes node1 and node2 (the nodes themselves, not just the data). If either of the given nodes is not in the linked list, does nothing.

2.2.20 void shuffle(int seed);
Shuffles the nodes of the linked list by swapping the nodes by applying the following algorithm:
for "i=0" to "i=size-1":
swap the node at index i with the node at index (i*i+seed)%size

2.2.21 LinkedList<T> &operator=(const LinkedList<T> &rhs);
This is the overloaded assignment operator. Removes all nodes in the linked list and the creates
new nodes by copying the nodes in the given rhs and inserts those new nodes into the linked list.



**--Music Streaming Service Implementation**

The music streaming platform in this project is implemented as the class MusicStream. MusicStream class has four
LinkedList objects in its private data field (namely profiles, artists, albums and songs) with the types Profile,
Artist, Album and Song, respectively. These four LinkedList objects keep the profiles, artists, albums and songs of the
music streaming service. Profile class represents the users of the music streaming service. Artist, Album and Song
classes represent the artists, albums and songs streamed on the music streaming service, respectively. Playlist class
represents the playlists created by the users of the music streaming service. Playlists of a user are kept in the user’s
corresponding Profile object.

The MusicStream, Profile, Playlist, Artist, Album and Song classes have their definitions in MusicStream.h, Profile.h,
Playlist.h, Artist.h, Album.h and Song.h files and their implementations in MusicStream.cpp, Profile.cpp, Playlist.cpp,
Artist.cpp, Album.cpp and Song.cpp files, respectively.


3.1 Song
Song objects keep name variable of type std::string, and duration and songId variables of type int to hold the data
related with available songs in the music streaming service. There is a public static Song variable
with name ADVERTISEMENT SONG in Song class. It will be used as the default Song object to put in the lists
of songs as advertisements. Further information is provided in following sections.


3.2 Album
Album objects keep name variable of type std::string and albumId variable of type int to hold the data related with
available albums in the music streming service. They also keep linked lists of pointers to the songs of the albums (namely
songs). Song pointers in the songs linked list are pointers to the Song objects stored in the linked lists in MusicStream
class. Following are the descriptions of the notable functions of this class:

3.2.1 void addSong(Song *song);
Adds (appends) the given song to the list of songs of this album. It's assumed that the given song
does not already exist in the list of songs of this album.

3.2.2 void dropSong(Song *song);
Removes the given song from the list of songs of this album. It's assumed that the given song
already exists in the list of songs of this album and there are no multiple occurrences.


3.3 Artist
Artist objects keep name variable of type std::string and artistId variable of type int to hold the data related
with available artists in the music streaming service. They also keep linked lists of pointers to the albums of the artists
(namely albums). Album pointers in the albums linked list are pointers to the Album objects stored in the linked lists
in MusicStream class. Following are the descriptions of the notable functions of this class:

3.3.1 void addAlbum(Album *album);
Adds (appends) the given album to the list of albums of this artist. It's assumed that the given song
does not already exist in the list of songs of this album.

3.2.2 void dropSong(Song *song);
Removes the given song from the list of songs of this album. It's assumed that the given song
already exists in the list of songs of this album and there are no multiple occurrences.


3.3 Artist
Artist objects keep name variable of type std::string and artistId variable of type int to hold the data related
with available artists in the music streaming service. They also keep linked lists of pointers to the albums of the artists
(namely albums). Album pointers in the albums linked list are pointers to the Album objects stored in the linked lists
in MusicStream class. Following are the descriptions of the notable functions of this class:

3.3.1 void addAlbum(Album *album);
Adds (appends) the given album to the list of albums of this artist. It's assumed that the given
album does not already exist in the list of albums of this artist.

3.3.2 void dropAlbum(Album *album);
Removes the given album from the list of albums of this artist. It's assumed that the given album
already exists in the list of albums of this artist and there are no multiple occurrences.


3.4 Playlist
Playlist objects keep name variable of type std::string, shared variable of type bool and playlistId variable of
type int to hold the data related with the playlists belonging to the users of the music streaming service. They also keep
linked lists of pointers to the songs in the playlists (namely songs). Song pointers in the songs linked list are pointers
to the Song objects stored in the linked lists in MusicStream class. Following are the descriptions of the notable functions of this class:

3.4.1 void Playlist::addSong(Song *song);
Adds (appends) the given song to the list of songs in this playlist. It's assumed that the given song
does not already exist in this playlist.

3.4.2 void Playlist::dropSong(Song *song);
Removes the given song from the list of songs in this playlist. It's assumed that the given song
already exists in this playlist and there are no multiple occurrences.

3.4.3 void Playlist::shuffle(int seed);
Shuffles the list of songs in this playlist. For shuffling, it uses shuffle(int seed) function of the LinkedList class with the
given seed.


3.5 Profile
Profile objects keep email and username variables of type std::string, and plan variable of type SubscriptionPlan
to hold the data related with the users of the music streaming service. SubscriptionPlan is an enumerated type
defined in Profile.h file with values free of charge, which means the user does not pay for the service and will listen
to advertisements between songs, and premium, which means the user pays for the service and will not listen to any
advertisement songs. A Profile object also keeps linked lists of (1) pointers to the profiles that the user follows (namely
following), (2) pointers to the profiles that follows the user (namely followers), and (3) the playlists belonging to the
user (namely playlists). Profile pointers in the following and followers linked lists are pointers to the Profile
objects stored in the linked lists in MusicStream class. Following are the descriptions of the notable functions of this class:

3.5.1 void followProfile(Profile *profile);
Makes this user (i.e., profile) follow the given profile. It's assumed that this user
is not already following the given profile.

3.5.2 void unfollowProfile(Profile *profile);
Makes this user unfollow the given profile. It's assumed that this user is already
following the given profile.

3.5.3 void createPlaylist(const std::string &playlistName);
Creates a new playlist with playlistName for this user.

3.5.4 void deletePlaylist(int playlistId);
Deletes the playlist with playlistId of this user. It's assumed that this user has a
playlist with playlistId.

3.5.5 void addSongToPlaylist(Song *song, int playlistId);
Adds the given song to the playlist with playlistId of this user. It's assumed that
this user has a playlist with playlistId and the given song is not already in the playlist.

3.5.6 void deleteSongFromPlaylist(Song *song, int playlistId);
Removes the given song from the playlist with playlistId of this user. It's assumed
that this user has a playlist with playlistId and the given song is already in the playlist.

3.5.7 Playlist *getPlaylist(int playlistId);
Gets (i.e., returns a pointer to) the playlist with playlistId of this user. It's assumed
that this user has a playlist with playlistId.

3.5.8 LinkedList<Playlist *> getSharedPlaylists();
Gets a linked list of (i.e., returns a linked list of pointers to) the playlists shared by the users who are
followed by this user.

3.5.9 void shufflePlaylist(int playlistId, int seed);
Shuffles the songs in the playlist with playlistId of this user. For shuffling, it uses shuffle(int seed)
function of the LinkedList class with the given seed. It's assumed that this user has a playlist
with playlistId.

3.5.10 void sharePlaylist(int playlistId);
Marks the playlist with playlistId of this user as shared. It's assumed that this
user has a playlist with playlistId.

3.5.11 void unsharePlaylist(int playlistId);
Marks the playlist with playlistId of this user as unshared. It's assumed that this
user has a playlist with playlistId.


3.6 MusicStream
In the MusicStream class, all member functions utilize profiles, artists, albums and songs member variables to
operate as described in the following subsections. Following are the descriptions of the notable functions of this class:

3.6.1 void addProfile(const std::string &email, const std::string &username, SubscriptionPlan plan);
Adds a new profile to the music streaming service (i.e., registers a new user). It takes the profile information
(email, username and plan) as parameters and inserts (appends) a new Profile object to the profiles linked list. It's assumed that
no profile with the given email is already registered.

3.6.2 void deleteProfile(const std::string &email);
Deletes a profile from the music streaming service (i.e., deletes an already registered user). It takes email of
the profile to delete (email) as parameter. Deletion of a user includes some steps: (1) deleting the user from its followers’
list of followings, (2) deleting the user from its followings’ list of followers, (3) deleting the content of the user’s Profile
object, and finally deleting the user’s Profile object from the MusicStream. It's assumed that a
profile with the given email is already registered.

3.6.3 void addArtist(const std::string &artistName);
Adds a new artist to the music streaming service. It takes the artist information (artistName) as parameter
and inserts (appends) a new Artist object to the artists linked list.

3.6.4 void addAlbum(const std::string &albumName, int artistId);
Adds a new album to the music streaming service. It takes the album information (artistName) and the
id of the artist that this album belongs to (artistId) as parameter and inserts (appends) a new Album object to the
albums linked list. It's assumed that an artist with the given artistId already exists in the
service.

3.6.5 void addSong(const std::string &songName, int songDuration, int albumId);
Adds a new song to the music streaming service. It takes the song information (songName and songDuration)
and the id of the album that this song belongs to (songId) as parameters and inserts (appends) a new Song object to the
songs linked list. It's assumed that an album with the given albumId already exists in the service.

3.6.6 void followProfile(const std::string &email1, const std::string &email2);
Takes the emails of two users (email1 and email2) as parameters and makes the user with email1 (i.e., first
user) follow the user with email2 (i.e., second user) by populating their corresponding Profile objects’ following and
followers lists. It's assumed that the given emails are different and profiles with the given emails
are already registered, and that the first user is not already following the second user.

3.6.7 void unfollowProfile(const std::string &email1, const std::string &email2);
Takes the emails of two users (email1 and email2) as parameters and makes the user with email1 (i.e., first
user) unfollow the user with email2 (i.e., second user) by populating their corresponding Profile objects’ following
and followers lists. It's assumed that the given emails are different and profiles with the given
emails are already registered, and that the first user is already following the second user.

3.6.8 void createPlaylist(const std::string &email, const std::string &playlistName);
Creates a new playlist with playlistName for the user with email. It's assumed that
a profile with the given email is already registered.

3.6.9 void deletePlaylist(const std::string &email, int playlistId);
Deletes the playlist with playlistId of the user with email. It's assumed that a
profile with the given email is already registered and it has a playlist with playlistId.

3.6.10 void addSongToPlaylist(const std::string &email, int songId, int playlistId);
Adds (not creates) the song with songId to the playlist with playlistId of the user with email. It's assumed that a 
profile with the given email is already registered, it has a playlist with playlistId
and the song with songId is not already in the playlist.

3.6.11 void deleteSongFromPlaylist(const std::string &email, int songId, int playlistId);
Removes the song with songId from the playlist with playlistId of the user with email. It's assumed that a profile with 
the given email is already registered, it has a playlist with playlistId and the song
with songId is already in the playlist.

3.6.12 LinkedList<Song *> playPlaylist(const std::string &email, Playlist *playlist);
Returns a linked list of pointers to the songs in the given playlist. If the user with email is subscribed
to the premium plan, you have to return the linked list of songs as it is. However, if the user is not subscribed to the
premium plan (i.e., has the free of charge plan), you have to return the linked list such that the default advertisement
song (Song::ADVERTISEMENT SONG) exists after every song. It's assumed that a profile with the
given email is already registered and the given playlist belongs to that profile or shared with that profile.

3.6.13 Playlist *getPlaylist(const std::string &email, int playlistId);
Gets (i.e., returns a pointer to) the playlist with playlistId of the user with email. It's assumed that a profile with 
the given email is already registered and it has a playlist with playlistId.

3.6.14 LinkedList<Playlist *> getSharedPlaylists(const std::string &email);
Gets a linked list of (i.e., returns a linked list of pointers to) the playlists shared by the users who are followed
by the user with email. It's assumed that a profile with the given email is already registered.

3.6.15 void shufflePlaylist(const std::string &email, int playlistId, int seed);
Shuffles the songs in the playlist with playlistId of the user with email. For shuffling, it uses shuffle(int
seed) function of the LinkedList class with the given seed. It's assumes that a profile with the
given email is already registered and it has a playlist with playlistId.

3.6.16 void sharePlaylist(const std::string &email, int playlistId);
Marks the playlist with playlistId of the user with email as shared. It's assumed
that a profile with the given email is already registered and it has a playlist with playlistId.

3.6.17 void unsharePlaylist(const std::string &email, int playlistId);
Marks the playlist with playlistId of the user with email as unshared. It's assumed
that a profile with the given email is already registered and it has a playlist with playlistId.

3.6.18 void subscribePremium(const std::string &email);
Changes the plan of the user with email to premium. It's assumed that a profile with
the given email is already registered.

3.6.19 void unsubscribePremium(const std::string &email);
Changes the plan of the user with email to free of charge. It's assumed that a
profile with the given email is already registered.

  
Spotify who amirite :)
