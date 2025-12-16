#include "playlist.h"

void createListPlaylist(ListPlaylist &L) {
    L.first = nullptr;
    L.last = nullptr;
}

bool isEmptyPlaylist(ListPlaylist L) {
    return (L.first == nullptr);
}


bool isEmptyVideo(adrPlaylist p) {
    return (p->firstVideo == nullptr);
}

adrPlaylist createElementPlaylist(string name, string playlistId) {
    adrPlaylist p = new elementPlaylist;
    p->info.name = name;
    p->info.playlistId = playlistId;
    p->next = nullptr;
    p->prev = nullptr;
    p->firstVideo = nullptr;
    return p;
}

adrVideo createElementVideo(string title, string id, string category) {
    adrVideo v = new elementVideo;
    v->info.title = title;
    v->info.id = id;
    v->info.category = category;
    v->next = nullptr;
    v->prev = nullptr;
    return v;
}

// Add playlist to the end of the list
void addPlaylist(ListPlaylist &L, adrPlaylist p) {
    if (isEmptyPlaylist(L)) {
        L.first = p;
        L.last = p;
    } else {
        L.last->next = p;
        p->prev = L.last;
        L.last = p;
    }
}

// Add video at the beginning of a playlist
void addVideoFirst(adrPlaylist p, adrVideo v) {
    if (isEmptyVideo(p)) {
        p->firstVideo = v;
    } else {
        v->next = p->firstVideo;
        p->firstVideo->prev = v;
        p->firstVideo = v;
    }
}

// Add video at the end of a playlist
void addVideoLast(adrPlaylist p, adrVideo v) {
    if (isEmptyVideo(p)) {
        p->firstVideo = v;
    } else {
        adrVideo current = p->firstVideo;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = v;
        v->prev = current;
    }
}

// Add video after a specific video in a playlist
void addVideoAfter(adrPlaylist p, adrVideo v, string afterVideoId) {
    if (!isEmptyVideo(p)) {
        adrVideo current = p->firstVideo;
        while (current != nullptr && current->info.id != afterVideoId) {
            current = current->next;
        }

        if (current != nullptr) {
            v->next = current->next;
            if (current->next != nullptr) {
                current->next->prev = v;
            }
            current->next = v;
            v->prev = current;
        }
    }
}

// Search for a playlist by ID
adrPlaylist searchPlaylist(ListPlaylist L, string playlistId) {
    adrPlaylist p = L.first;
    while (p != nullptr) {
        if (p->info.playlistId == playlistId) {
            return p;
        }
        p = p->next;
    }
    return nullptr;
}

// Search for a video by ID within a playlist
adrVideo searchVideo(adrPlaylist p, string videoId) {
    if (!isEmptyVideo(p)) {
        adrVideo v = p->firstVideo;
        while (v != nullptr) {
            if (v->info.id == videoId) {
                return v;
            }
            v = v->next;
        }
    }
    return nullptr;
}

// Delete specific video in a playlist
void deleteVideo(adrPlaylist p, string afterVideoId) {
    if (!isEmptyVideo(p)) {
        adrVideo current = searchVideo(p, afterVideoId);

        if (current != nullptr && current->next != nullptr) {
            adrVideo prevC = current->prev;
            prevC->next = current->next;
            current->next->prev = prevC;

            delete current;
        }
    }
}

// Delete a playlist and all its videos
void deletePlaylist(ListPlaylist &L, string playlistId) {
    adrPlaylist p = searchPlaylist(L, playlistId);

    if (p != nullptr) {
        // Delete all videos in the playlist
        while (!isEmptyVideo(p)) {
            deleteVideoFirst(p);
        }

        // Remove playlist from the list
        if (p->prev != nullptr) {
            p->prev->next = p->next;
        } else {
            L.first = p->next;
        }

        if (p->next != nullptr) {
            p->next->prev = p->prev;
        } else {
            L.last = p->prev;
        }

        delete p;
    }
}

// Display all playlists and their videos
void displayAllPlaylists(ListPlaylist L) {
    adrPlaylist p = L.first;
    while (p != nullptr) {
        cout << "\n=== Playlist: " << p->info.name << " (" << p->info.playlistId << ") ===" << endl;

        adrVideo v = p->firstVideo;
        if (v == nullptr) {
            cout << "No videos in this playlist." << endl;
        } else {
            int count = 1;
            while (v != nullptr) {
                cout << count << ". " << v->info.title
                     << " [" << v->info.id << "]"
                     << " - Category: " << v->info.category << endl;
                v = v->next;
                count++;
            }
        }
        p = p->next;
    }
}

// Display videos by category across all playlists
void displayVideosByCategory(ListPlaylist L, string category) {
    cout << "\n=== Videos in Category: " << category << " ===" << endl;

    adrPlaylist p = L.first;
    bool found = false;

    while (p != nullptr) {
        adrVideo v = p->firstVideo;
        while (v != nullptr) {
            if (v->info.category == category) {
                cout << "Playlist: " << p->info.name
                     << " | Video: " << v->info.title
                     << " [" << v->info.id << "]" << endl;
                found = true;
            }
            v = v->next;
        }
        p = p->next;
    }

    if (!found) {
        cout << "No videos found in this category." << endl;
    }
}
