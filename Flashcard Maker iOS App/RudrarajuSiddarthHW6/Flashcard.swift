//
//  Flashcard.swift
//  RudrarajuSiddarthHW6
//
//  Created by Siddarth Rudraraju on 3/18/24.
//

import Foundation

struct Flashcard: Identifiable, Codable, Hashable {
    var id: String
    var question: String
    var answer: String
    var isFavorite: Bool

    init(id: String = UUID().uuidString, question: String, answer: String, isFavorite: Bool = false) {
        self.id = id
        self.question = question
        self.answer = answer
        self.isFavorite = isFavorite
    }
}
