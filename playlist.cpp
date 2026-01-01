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
    // SIMPLE VERSION - just create, don't check duplicates here
    adrVideo v = new elementVideo;
    v->info.title = title;
    v->info.id = id;
    v->info.category = category;
    v->next = nullptr;
    v->prev = nullptr;
    return v;
}

// Add playlist to the end of the list
void addPlaylist(ListPlaylist &L, adrPlaylist pl) {
    // Check if playlist ID already exists in the list
    adrPlaylist current = L.first;
    while (current != nullptr) {
        if (current->info.playlistId == pl->info.playlistId) {
            cout << "Error: Playlist ID '" << pl->info.playlistId << "' already exists!" << endl;
            delete pl;  // Free the memory since we won't use it
            return;
        }
        current = current->next;
    }
    
    // Add to list if ID is unique
    if (L.first == nullptr) {
        L.first = pl;
        L.last = pl;
    } else {
        L.last->next = pl;
        pl->prev = L.last;
        L.last = pl;
    }
}

bool checkDuplicateVideo(adrPlaylist p, adrVideo v) {
    adrVideo current = p->firstVideo;
    while (current != nullptr) {
        if (current->info.id == v->info.id) {
            return true;
        }
        current = current->next;
    }
    return false;
}
// Add video at the beginning of a playlist
void addVideoFirst(adrPlaylist p, adrVideo v) {
    if (checkDuplicateVideo(p, v)) {
        cout << "Error: Video ID '" << v->info.id << "' already exists!" << endl;
        delete v;
        return;
    }

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
    if (checkDuplicateVideo(p, v)) {
        cout << "Error: Video ID '" << v->info.id << "' already exists!" << endl;
        delete v;
        return;
    }

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
    if (checkDuplicateVideo(p, v)) {
        cout << "Error: Video ID '" << v->info.id << "' already exists!" << endl;
        delete v;
        return;
    }
    
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
void deleteVideo(adrPlaylist p, string videoId) {
    if (isEmptyVideo(p)) return;
    
    adrVideo current = searchVideo(p, videoId);
    if (current == nullptr) return;  // Video not found
    
    // Update previous pointer
    if (current->prev != nullptr) {
        current->prev->next = current->next;
    } else {
        // current is the first video
        p->firstVideo = current->next;
    }
    
    // Update next pointer
    if (current->next != nullptr) {
        current->next->prev = current->prev;
    }
    
    delete current;
}

void deleteVideoFirst(adrPlaylist p){
    if (p->firstVideo != nullptr){
        adrVideo temp = p->firstVideo;
        p->firstVideo = temp->next;
        if (p->firstVideo != nullptr) {
            p->firstVideo->prev = nullptr;
        }
        delete temp;
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
