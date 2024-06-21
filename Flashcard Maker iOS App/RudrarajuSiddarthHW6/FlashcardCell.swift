//
//  FlashcardCell.swift
//  RudrarajuSiddarthHW6
//
//  Created by Siddarth Rudraraju on 3/18/24.
//

import Foundation

import SwiftUI

struct FlashcardCell: View {
    let flashcard: Flashcard
    
    var body: some View {
        VStack(alignment: .leading, spacing: 12) {
            Text(flashcard.question)
                .font(.title3)
            Text(flashcard.answer)
                .font(.subheadline)
        }
    }
}

