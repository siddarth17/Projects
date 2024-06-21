//
//  FlashcardViewModel.swift
//  RudrarajuSiddarthHW6
//
//  Created by Siddarth Rudraraju on 3/18/24.
//

import Foundation
import SwiftUI

class FlashcardViewModel: ObservableObject, FlashcardsModel {
    @Published var flashcards: [Flashcard] {
        didSet {
            saveToDisk()
        }
    }
    @Published var currentIndex: Int = 0 {
        didSet {
            if flashcards.isEmpty {
                currentIndex = 0
            } else if currentIndex >= flashcards.count {
                currentIndex = 0
            } else if currentIndex < 0 {
                currentIndex = flashcards.count - 1
            }
        }
    }

    private var flashcardsFilePath: URL {
        guard let path = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask).first else {
            fatalError("Document directory not accessible")
        }
        return path.appendingPathComponent("flashcards.json")
    }

    init() {
        self.flashcards = []
        loadFromDisk()
    }

    private func loadFromDisk() {
        do {
            let data = try Data(contentsOf: flashcardsFilePath)
            self.flashcards = try JSONDecoder().decode([Flashcard].self, from: data)
        } catch {
            print("Failed to load flashcards from disk with error: \(error.localizedDescription)")
            self.flashcards = []
        }
    }

    private func saveToDisk() {
        do {
            let data = try JSONEncoder().encode(flashcards)
            try data.write(to: flashcardsFilePath, options: [.atomicWrite, .completeFileProtection])
            print("Flashcards saved successfully")
        } catch {
            print("Failed to save flashcards to disk with error: \(error.localizedDescription)")
        }
    }
    
    var currentFlashcard: Flashcard? {
        if flashcards.isEmpty {
            return nil
        } else {
            return flashcards[currentIndex]
        }
    }

    var favoriteFlashcards: [Flashcard] {
        return flashcards.filter { $0.isFavorite }
    }

    var numberOfFlashcards: Int {
        return flashcards.count
    }

    func randomize() {
        if !flashcards.isEmpty {
            currentIndex = Int.random(in: 0..<flashcards.count)
        }
    }

    func next() {
        if !flashcards.isEmpty {
            currentIndex += 1
            if currentIndex >= flashcards.count {
                currentIndex = 0
            }
        }
    }

    func previous() {
        if !flashcards.isEmpty {
            currentIndex -= 1
            if currentIndex < 0 {
                currentIndex = flashcards.count - 1
            }
        }
    }

    func flashcard(at index: Int) -> Flashcard? {
        if index >= 0 && index < flashcards.count {
            return flashcards[index]
        } else {
            return nil
        }
    }

    func append(flashcard: Flashcard) {
        flashcards.append(flashcard)
    }

    func insert(flashcard: Flashcard, at index: Int) {
        if index >= 0 && index < flashcards.count {
            flashcards.insert(flashcard, at: index)
        } else {
            flashcards.append(flashcard)
        }
    }

    func removeFlashcard(at index: Int) {
        if index >= 0 && index < flashcards.count {
            flashcards.remove(at: index)
        }
    }

    func getIndex(for flashcard: Flashcard) -> Int? {
        for (index, item) in flashcards.enumerated() {
            if item.id == flashcard.id {
                return index
            }
        }
        return nil
    }

    func update(flashcard: Flashcard, at index: Int) {
            guard index >= 0, index < flashcards.count else {
                print("Index out of bounds")
                return
            }
            flashcards[index] = flashcard
    }

    func toggleFavorite() {
        if currentIndex >= 0 && currentIndex < flashcards.count {
            flashcards[currentIndex].isFavorite.toggle()
        }
    }
    
    func toggleFavorite(at index: Int) {
        guard index >= 0, index < flashcards.count else { return }
        flashcards[index].isFavorite.toggle()
        saveToDisk()
    }

}

