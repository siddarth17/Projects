//
//  FavoritesFlashcardListPage.swift
//  RudrarajuSiddarthHW6
//
//  Created by Siddarth Rudraraju on 3/18/24.
//

import Foundation
import SwiftUI

struct FavoritesFlashcardListPage: View {
    @EnvironmentObject var flashcardViewModel: FlashcardViewModel

    var body: some View {
        NavigationStack {
            List(flashcardViewModel.favoriteFlashcards) { flashcard in
                NavigationLink(value: flashcard) {
                    FlashcardCell(flashcard: flashcard)
                }
            }
            .navigationTitle("Favorites")
            .navigationDestination(for: Flashcard.self) { flashcard in
                EditFlashCardPage(flashcard: flashcard)
            }
        }
    }
}
