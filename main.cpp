#include <iostream>
#include "playlist.h"
using namespace std;

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

    adrPlaylist p1 = createElementPlaylist("Materi_Kuliah", "P001");
    addPlaylist(L, p1);
    // Isi video ke Playlist 1
    addVideoLast(p1, createElementVideo("Intro_C++", "V001", "Educational"));
    addVideoLast(p1, createElementVideo("Linked_List", "V002", "Educational"));
    addVideoLast(p1, createElementVideo("Stack_Queue", "V003", "Educational"));

    // 2. Buat Playlist Kedua: Hiburan Weekend
    adrPlaylist p2 = createElementPlaylist("Hiburan_Weekend", "P002");
    addPlaylist(L, p2);
    // Isi video ke Playlist 2
    addVideoLast(p2, createElementVideo("Minecraft_Survival", "V004", "Gaming"));
    addVideoLast(p2, createElementVideo("Daily_Vlog_Japan", "V005", "Vlog"));

    // 3. Buat Playlist Ketiga: Musik Fokus
    adrPlaylist p3 = createElementPlaylist("Musik_Fokus", "P003");
    addPlaylist(L, p3);
    // Isi video ke Playlist 3
    addVideoLast(p3, createElementVideo("Lofi_Beats", "V006", "Music"));
    addVideoLast(p3, createElementVideo("Piano_Classic", "V007", "Music"));
    
    int choice;
    string name, id, category, playlistId, VideoId;
    int addChoice, deleteChoice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: { // Create Playlist
              cout << "\n--- Create New Playlist ---" << endl;
                // Show current playlists FIRST
                 cout << "\nCurrent playlists before adding:" << endl;
            adrPlaylist temp = L.first;
            while (temp != nullptr) {
                cout << "- " << temp->info.name << " (" << temp->info.playlistId << ")" << endl;
                temp = temp->next;
            }
            
            cout << "\nEnter playlist name: ";
            cin >> name;
            cout << "Enter playlist ID: ";
            cin >> id;
            
            adrPlaylist newPlaylist = createElementPlaylist(name, id);
            addPlaylist(L, newPlaylist);
            
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
                        cin >> VideoId;
                        addVideoAfter(targetPlaylist, newVideo, VideoId);
                        cout << "Video added after video ID: " << VideoId << endl;
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
                        cin >> VideoId;
                        deleteVideo(targetPlaylist, VideoId);
                        cout << "Video deleted ID: " << VideoId << endl;
                        break;
                    
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
