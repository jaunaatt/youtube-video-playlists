#ifndef PLAYLIST_H_INCLUDED
#define PLAYLIST_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

struct Video {
    string title;
    string id;
    string category;
};

struct Playlist {
    string name;
    string playlistId;
};

struct elementVideo;
struct elementPlaylist;

typedef elementPlaylist* adrPlaylist;
typedef elementVideo* adrVideo;

struct elementPlaylist {
    Playlist info;
    adrPlaylist next;
    adrPlaylist prev;
    adrVideo firstVideo;
};

struct elementVideo {
    Video info;
    adrVideo next;
    adrVideo prev;
};

struct ListPlaylist {
    adrPlaylist first;
    adrPlaylist last;
};


void createListPlaylist(ListPlaylist &L);
bool isEmptyPlaylist(ListPlaylist L);
bool isEmptyVideo(adrPlaylist p);

adrPlaylist createElementPlaylist(string name, string playlistId);
adrVideo createElementVideo(string title, string id, string category);

void addPlaylist(ListPlaylist &L, adrPlaylist p);
void addVideoFirst(adrPlaylist p, adrVideo v);
void addVideoLast(adrPlaylist p, adrVideo v);
void addVideoAfter(adrPlaylist p, adrVideo v, string VideoId);

adrPlaylist searchPlaylist(ListPlaylist L, string playlistId);
adrVideo searchVideo(adrPlaylist p, string videoId);

void deleteVideo(adrPlaylist p, string VideoId);
void deleteVideoFirst(adrPlaylist p);

void deletePlaylist(ListPlaylist &L, string playlistId);

void displayAllPlaylists(ListPlaylist L);
void displayVideosByCategory(ListPlaylist L, string category);

#endif // PLAYLIST_H_INCLUDED
