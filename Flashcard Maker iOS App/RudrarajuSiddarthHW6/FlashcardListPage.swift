//
//  FlashcardListPage.swift
//  RudrarajuSiddarthHW6
//
//  Created by Siddarth Rudraraju on 3/18/24.
//

import Foundation
import SwiftUI

struct FlashcardListPage: View {
    @EnvironmentObject var flashcardViewModel: FlashcardViewModel
    
    var body: some View {
        NavigationStack {
            List {
                ForEach($flashcardViewModel.flashcards) { $flashcard in
                    NavigationLink(value: flashcard) {
                        FlashcardCell(flashcard: flashcard)
                    }
                }
                .onDelete(perform: deleteItems)
            }
            .navigationTitle("Flashcards")
            .toolbar {
                NavigationLink(destination: EditFlashCardPage()) {
                    Image(systemName: "plus")
                }
            }
            .navigationDestination(for: Flashcard.self) { flashcard in
                EditFlashCardPage(flashcard: flashcard)
            }
        }
    }
    
    private func deleteItems(at offsets: IndexSet) {
        flashcardViewModel.flashcards.remove(atOffsets: offsets)
    }
}
