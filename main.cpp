#include "playlist.h"

void showMenu() {
    cout << "\n===== VIDEO PLAYLIST MANAGEMENT SYSTEM =====" << endl;
    cout << "1. Create Playlist" << endl;
    cout << "2. Add Video to Playlist" << endl;
    cout << "3. Delete Video from Playlist" << endl;
    cout << "4. Delete Playlist" << endl;
    cout << "5. Display All Playlists" << endl;
    cout << "6. Display Videos by Category" << endl;
    cout << "7. Exit" << endl;
    cout << "==========================================" << endl;
    cout << "Enter your choice: ";
}

int main() {
    ListPlaylist L;
    createListPlaylist(L);

    // Add some sample playlists
    adrPlaylist p1 = createElementPlaylist("Gaming", "P001");
    adrPlaylist p2 = createElementPlaylist("Educational", "P002");
    addPlaylist(L, p1);
    addPlaylist(L, p2);

    // Add some sample videos
    adrVideo v1 = createElementVideo("GameReview", "V001", "Gaming");
    adrVideo v2 = createElementVideo("TravelVlog", "V002", "Vlog");
    adrVideo v3 = createElementVideo("DataStructures", "V003", "Educational");
    adrVideo v4 = createElementVideo("ChillMusic", "V004", "Music");

    addVideoFirst(p1, v1);
    addVideoLast(p1, v2);
    addVideoFirst(p2, v3);
    addVideoLast(p2, v4);

    int choice;
    string name, id, category, playlistId, afterVideoId;
    int addChoice, deleteChoice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: { // Create Playlist
                cout << "\n--- Create New Playlist ---" << endl;
                cout << "Enter playlist name (no spaces): ";
                cin >> name;
                cout << "Enter playlist ID: ";
                cin >> id;

                adrPlaylist newPlaylist = createElementPlaylist(name, id);
                addPlaylist(L, newPlaylist);
                cout << "Playlist created successfully!" << endl;
                break;
            }

            case 2: { // Add Video to Playlist
                cout << "\n--- Add Video to Playlist ---" << endl;
                cout << "Enter target playlist ID: ";
                cin >> playlistId;

                adrPlaylist targetPlaylist = searchPlaylist(L, playlistId);
                if (targetPlaylist != nullptr) {
                    cout << "Enter video title (no spaces): ";
                    cin >> name;
                    cout << "Enter video ID: ";
                    cin >> id;
                    cout << "Enter category (Gaming/Vlog/Music/Educational): ";
                    cin >> category;

                    cout << "\nAdd at: 1. First  2. Last  3. After specific video: ";
                    cin >> addChoice;

                    adrVideo newVideo = createElementVideo(name, id, category);

                    if (addChoice == 1) {
                        addVideoFirst(targetPlaylist, newVideo);
                        cout << "Video added at the beginning." << endl;
                    } else if (addChoice == 2) {
                        addVideoLast(targetPlaylist, newVideo);
                        cout << "Video added at the end." << endl;
                    } else if (addChoice == 3) {
                        cout << "Enter video ID to add after: ";
                        cin >> afterVideoId;
                        addVideoAfter(targetPlaylist, newVideo, afterVideoId);
                        cout << "Video added after video ID: " << afterVideoId << endl;
                    }
                } else {
                    cout << "Playlist not found!" << endl;
                }
                break;
            }

            case 3: { // Delete Video from Playlist
                cout << "\n--- Delete Video from Playlist ---" << endl;
                cout << "Enter playlist ID: ";
                cin >> playlistId;

                adrPlaylist targetPlaylist = searchPlaylist(L, playlistId);
                if (targetPlaylist != nullptr) {
                        cout << "Enter video ID to delete: ";
                        cin >> afterVideoId;
                        deleteVideoAfter(targetPlaylist, afterVideoId);
                        cout << "Video deleted after video ID: " << afterVideoId << endl;
                    }
                } else {
                    cout << "Playlist not found!" << endl;
                }
                break;
            }

            case 4: { // Delete Playlist
                cout << "\n--- Delete Playlist ---" << endl;
                cout << "Enter playlist ID to delete: ";
                cin >> playlistId;
                deletePlaylist(L, playlistId);
                cout << "Playlist deleted if it existed." << endl;
                break;
            }

            case 5: // Display All Playlists
                cout << "\n--- All Playlists ---" << endl;
                displayAllPlaylists(L);
                break;

            case 6: { // Display Videos by Category
                cout << "\n--- Display Videos by Category ---" << endl;
                cout << "Enter category (Gaming/Vlog/Music/Educational): ";
                cin >> category;
                displayVideosByCategory(L, category);
                break;
            }

            case 7: // Exit
                cout << "Exiting program. Goodbye!" << endl;
                break;

            default:
                cout << "Invalid choice! Please try again." << endl;
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();  // Clear buffer for next iteration
        cin.get();     // Wait for Enter key

    } while (choice != 7);

    return 0;
}
