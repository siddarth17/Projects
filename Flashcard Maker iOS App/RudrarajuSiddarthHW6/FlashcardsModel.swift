//
//  FlashcardsModel.swift
//  RudrarajuSiddarthHW6
//
//  Created by Siddarth Rudraraju on 3/18/24.
//

import Foundation

protocol FlashcardsModel {
    var numberOfFlashcards: Int { get }
    var currentFlashcard: Flashcard? { get }
    var favoriteFlashcards: [Flashcard] { get }
    func randomize()
    func next()
    func previous()
    func flashcard(at index: Int) -> Flashcard?
    func append(flashcard: Flashcard)
    func insert(flashcard: Flashcard, at index: Int)
    func removeFlashcard(at index: Int)
    func getIndex(for flashcard: Flashcard) -> Int?
    func update(flashcard: Flashcard, at index: Int)
    func toggleFavorite()
}

