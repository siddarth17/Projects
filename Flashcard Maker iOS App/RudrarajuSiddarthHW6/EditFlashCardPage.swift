//
//  EditFlashCardPage.swift
//  RudrarajuSiddarthHW6
//
//  Created by Siddarth Rudraraju on 3/18/24.
//

import Foundation
import SwiftUI

struct EditFlashCardPage: View {
    @Environment(\.dismiss) private var dismiss
    @EnvironmentObject var flashcardViewModel: FlashcardViewModel
    
    private var flashcard: Flashcard?
    @State private var question: String = ""
    @State private var answer: String = ""
    @State private var isFavorite: Bool = false

    init(flashcard: Flashcard? = nil) {
        self.flashcard = flashcard
        if let flashcard = flashcard {
            _question = State(initialValue: flashcard.question)
            _answer = State(initialValue: flashcard.answer)
            _isFavorite = State(initialValue: flashcard.isFavorite)
        }
    }

    var body: some View {
        VStack(spacing: 24) {
            TextField("Question", text: $question)
            TextField("Answer", text: $answer)
            Toggle(isOn: $isFavorite) {
                Text("Favorite")
            }
            Spacer()
        }
        .padding()
        .navigationTitle(flashcard == nil ? "New Card" : "Edit Card")
        .toolbar {
            Button("Save") {
                let newOrEditedFlashcard = Flashcard(id: flashcard?.id ?? UUID().uuidString, question: question, answer: answer, isFavorite: isFavorite)
                if let flashcard = flashcard {
                    flashcardViewModel.update(flashcard: newOrEditedFlashcard, at: flashcardViewModel.getIndex(for: flashcard) ?? 0)
                } else {
                    flashcardViewModel.append(flashcard: newOrEditedFlashcard)
                }
                dismiss()
            }
            .disabled(question.isEmpty || answer.isEmpty)
        }
    }
}
