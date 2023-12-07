#!/usr/bin/env python3

from dataclasses import dataclass

@dataclass
class Card:
    """Dataclass for a scratch card with id, game numbers, and winning numbers."""

    game_id: int
    game_nums: set[str]
    chosen_nums: set[str]

    def num_copies(self) -> int:
        intersects = self.chosen_nums.intersection(self.game_nums)
        #print(self.game_id, intersects)
        return len(intersects)


def count_cards(input_text: str) -> int:
    """Split the input into lines, convert each line into a Card object and append to a list of cards.
    Iterate over the list of cards and add copies to the list as needed modifying the list inplace.
    Return the length of the final list

    Args:
        input_text: Raw input text.

    Returns:
        Total number of created scratch cards.
    """
    lines = input_text.splitlines()
    cards = []
    for game_id, line in enumerate(lines):
        numbers = line.split(": ")[1]
        cards.append(
            Card(
                game_id + 1,
                *map(set, map(str.split, map(str.strip, numbers.split(" | ")))),
            )
        )
    for card in cards:
        num_copies = card.num_copies()
        #print(f"num copies: {num_copies}")
        #print(card.game_id, len(cards), len(cards[card.game_id : card.game_id + num_copies]))
        cards.extend(cards[card.game_id : card.game_id + num_copies])

    return len(cards)

def main():
    with open("input.txt", 'r') as f:
        data = f.read()
    sum = count_cards(data)
    print(sum)

if __name__ == "__main__":
    main()