//
//  FlashcardPage.swift
//  RudrarajuSiddarthHW6
//
//  Created by Siddarth Rudraraju on 3/18/24.
//

import Foundation
import SwiftUI

struct FlashcardPage: View {
    let OFFSET_X: CGFloat = 450.0
    let OFFSET_Y: CGFloat = 900.0

    @EnvironmentObject var flashcardViewModel: FlashcardViewModel
    @State var isShowingQuestion = true
    @State var offsetX: CGFloat = 0.0
    @State var offsetY: CGFloat = 0.0
    @State var isHidden = false

    var title: String {
        guard let currentCard = flashcardViewModel.currentFlashcard else { return "" }
        return isShowingQuestion ? currentCard.question : currentCard.answer
    }

    var isFavorite: Bool {
        flashcardViewModel.currentFlashcard?.isFavorite ?? false
    }

    var body: some View {
        ZStack(alignment: .topTrailing) {
            VStack {
                Text(title)
                    .font(.largeTitle)
                    .bold()
                    .foregroundColor(isShowingQuestion ? .blue : .green)
                    .padding()
                    .opacity(isHidden ? 0 : 1)
                    .offset(x: offsetX, y: offsetY)
                    .frame(maxWidth: .infinity, maxHeight: .infinity)
                    .background(Color.white)
                    .onTapGesture(count: 2) {
                        withAnimation {
                            toggleQuestionAnswer()
                        }
                    }
                    .onTapGesture {
                        withAnimation {
                            showRandomFlashCard()
                        }
                    }
                    .gesture(
                        DragGesture(minimumDistance: 3.0, coordinateSpace: .local)
                            .onEnded { value in
                                handleSwipe(value.translation)
                            }
                    )
            }
            Button(action: {
                if let index = flashcardViewModel.getIndex(for: flashcardViewModel.currentFlashcard!) {
                    flashcardViewModel.toggleFavorite(at: index)
                }
            }) {
                Image(systemName: isFavorite ? "star.fill" : "star")
                    .padding()
                    .foregroundColor(isFavorite ? .yellow : .gray)
            }
            .padding(.top, 44) // Adjust based on your UI needs
            .padding(.trailing, 20) // Adjust based on your UI needs
        }
    }

    func showRandomFlashCard() {
        isHidden = true
        offsetY = -OFFSET_Y
        DispatchQueue.main.asyncAfter(deadline: .now() + 0.3) {
            flashcardViewModel.randomize()
            isShowingQuestion = true
            offsetY = OFFSET_Y
            DispatchQueue.main.asyncAfter(deadline: .now() + 0.3) {
                withAnimation {
                    isHidden = false
                    offsetY = 0
                }
            }
        }
    }

    func toggleQuestionAnswer() {
        isShowingQuestion.toggle()
    }

    func showNextCard() {
        isHidden = true
        offsetX = -OFFSET_X
        DispatchQueue.main.asyncAfter(deadline: .now() + 0.3) {
            flashcardViewModel.next()
            isShowingQuestion = true
            offsetX = OFFSET_X
            DispatchQueue.main.asyncAfter(deadline: .now() + 0.3) {
                withAnimation {
                    isHidden = false
                    offsetX = 0
                }
            }
        }
    }

    func showPreviousCard() {
        isHidden = true
        offsetX = OFFSET_X
        DispatchQueue.main.asyncAfter(deadline: .now() + 0.3) {
            flashcardViewModel.previous()
            isShowingQuestion = true
            offsetX = -OFFSET_X
            DispatchQueue.main.asyncAfter(deadline: .now() + 0.3) {
                withAnimation {
                    isHidden = false
                    offsetX = 0
                }
            }
        }
    }

    func handleSwipe(_ translation: CGSize) {
        if abs(translation.width) > abs(translation.height) {
            if translation.width < 0 {
                // left swipe
                withAnimation {
                    showNextCard()
                }
            } else {
                // right swipe
                withAnimation {
                    showPreviousCard()
                }
            }
        }
    }
}

#Preview {
    FlashcardPage()
}
