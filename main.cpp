#include "Card.h"
#include "Collection.h"
#include <chrono>
#include <random>

int main()
{
    // For each item in the Collection, keeps track of how many times that item has been sorted into each index.
    cout << "Runtime and Randomness Tests:" << endl;
    vector<vector<int>> gdlevineRuntimesMatrix = vector<vector<int>>(12);
    vector<vector<int>> gdlevineItemsPlacementMatrix = vector<vector<int>>(12);
    // Test with a standard Deck.
    vector<Card> stdCards;
    stdCards.push_back(Card(Card::ace, Card::clubs, 0));
    stdCards.push_back(Card(Card::two, Card::clubs, 1));
    stdCards.push_back(Card(Card::three, Card::clubs, 2));
    stdCards.push_back(Card(Card::four, Card::clubs, 3));
    stdCards.push_back(Card(Card::five, Card::clubs, 4));
    stdCards.push_back(Card(Card::six, Card::clubs, 5));
    stdCards.push_back(Card(Card::seven, Card::clubs, 6));
    stdCards.push_back(Card(Card::eight, Card::clubs, 7));
    stdCards.push_back(Card(Card::nine, Card::clubs, 8));
    stdCards.push_back(Card(Card::ten, Card::clubs, 9));
    stdCards.push_back(Card(Card::jack, Card::clubs, 10));
    stdCards.push_back(Card(Card::queen, Card::clubs, 11));
    stdCards.push_back(Card(Card::king, Card::clubs, 12));
    stdCards.push_back(Card(Card::ace, Card::diamonds, 13));
    stdCards.push_back(Card(Card::two, Card::diamonds, 14));
    stdCards.push_back(Card(Card::three, Card::diamonds, 15));
    stdCards.push_back(Card(Card::four, Card::diamonds, 16));
    stdCards.push_back(Card(Card::five, Card::diamonds, 17));
    stdCards.push_back(Card(Card::six, Card::diamonds, 18));
    stdCards.push_back(Card(Card::seven, Card::diamonds, 19));
    stdCards.push_back(Card(Card::eight, Card::diamonds, 20));
    stdCards.push_back(Card(Card::nine, Card::diamonds, 21));
    stdCards.push_back(Card(Card::ten, Card::diamonds, 22));
    stdCards.push_back(Card(Card::jack, Card::diamonds, 23));
    stdCards.push_back(Card(Card::queen, Card::diamonds, 24));
    stdCards.push_back(Card(Card::king, Card::diamonds, 25));
    stdCards.push_back(Card(Card::ace, Card::hearts, 26));
    stdCards.push_back(Card(Card::two, Card::hearts, 27));
    stdCards.push_back(Card(Card::three, Card::hearts, 28));
    stdCards.push_back(Card(Card::four, Card::hearts, 29));
    stdCards.push_back(Card(Card::five, Card::hearts, 30));
    stdCards.push_back(Card(Card::six, Card::hearts, 31));
    stdCards.push_back(Card(Card::seven, Card::hearts, 32));
    stdCards.push_back(Card(Card::eight, Card::hearts, 33));
    stdCards.push_back(Card(Card::nine, Card::hearts, 34));
    stdCards.push_back(Card(Card::ten, Card::hearts, 35));
    stdCards.push_back(Card(Card::jack, Card::hearts, 36));
    stdCards.push_back(Card(Card::queen, Card::hearts, 37));
    stdCards.push_back(Card(Card::king, Card::hearts, 38));
    stdCards.push_back(Card(Card::ace, Card::spades, 39));
    stdCards.push_back(Card(Card::two, Card::spades, 40));
    stdCards.push_back(Card(Card::three, Card::spades, 41));
    stdCards.push_back(Card(Card::four, Card::spades, 42));
    stdCards.push_back(Card(Card::five, Card::spades, 43));
    stdCards.push_back(Card(Card::six, Card::spades, 44));
    stdCards.push_back(Card(Card::seven, Card::spades, 45));
    stdCards.push_back(Card(Card::eight, Card::spades, 46));
    stdCards.push_back(Card(Card::nine, Card::spades, 47));
    stdCards.push_back(Card(Card::ten, Card::spades, 48));
    stdCards.push_back(Card(Card::jack, Card::spades, 49));
    stdCards.push_back(Card(Card::queen, Card::spades, 50));
    stdCards.push_back(Card(Card::king, Card::spades, 51));
    cout << "Testing gdlevineRandomize with a standard deck (and gathering data, which takes the bulk of the time)..." << endl;
    gdlevineItemsPlacementMatrix[0] = vector<int>(stdCards.size());
    for(int i = 0; i < 100; i++)
    {
        Collection<Card> stdDeck;
        stdDeck.setItems(stdCards);

        auto startMilli = chrono::steady_clock::now();
        stdDeck.gdlevineRandomize();
        gdlevineRuntimesMatrix[0].push_back(chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - startMilli).count());

        for(int j = 0; j < stdDeck.getItems().size(); j++)
        {
            gdlevineItemsPlacementMatrix[0][j] += stdDeck.getItemsNewPosByOldIndex()[j];
        }
    }
    cout << "Done." << endl;
    // Test with a sorted deck.
    Collection<Card> tempDeck;
    tempDeck.setItems(stdCards);
    tempDeck.sort();
    vector<Card> sortedCards = tempDeck.getItems();
    cout << "Testing gdlevineRandomize with a sorted deck (and gathering data, which takes the bulk of the time)..." << endl;
    gdlevineItemsPlacementMatrix[1] = vector<int>(sortedCards.size());
    for(int i = 0; i < 100; i++)
    {
        Collection<Card> sortedDeck;
        sortedDeck.setItems(sortedCards);

        auto startMilli = chrono::steady_clock::now();
        sortedDeck.gdlevineRandomize();
        gdlevineRuntimesMatrix[1].push_back(chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - startMilli).count());

        for(int j = 0; j < sortedDeck.getItems().size(); j++)
        {
            gdlevineItemsPlacementMatrix[1][j] += sortedDeck.getItemsNewPosByOldIndex()[j];
        }
    }
    cout << "Done." << endl;
    // Test with a sorted deck in reverse order.
    reverse(sortedCards.begin(), sortedCards.end());
    cout << "Testing gdlevineRandomize with a sorted deck in reverse order (and gathering data, which takes the bulk of the time)..." << endl;
    gdlevineItemsPlacementMatrix[2] = vector<int>(sortedCards.size());
    for(int i = 0; i < 100; i++)
    {
        Collection<Card> reversedDeck;
        reversedDeck.setItems(sortedCards);

        auto startMilli = chrono::steady_clock::now();
        reversedDeck.gdlevineRandomize();
        gdlevineRuntimesMatrix[2].push_back(chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - startMilli).count());

        for(int j = 0; j < reversedDeck.getItems().size(); j++)
        {
            gdlevineItemsPlacementMatrix[2][j] += reversedDeck.getItemsNewPosByOldIndex()[j];
        }
    }
    cout << "Done." << endl;
    // Test with already-random decks.
    Collection<Card> randDeck;
    randDeck.setItems(stdCards);
    randDeck.gdlevineRandomize();
    cout << "Testing gdlevineRandomize with already-random decks (and gathering data, which takes the bulk of the time)..." << endl;
    gdlevineItemsPlacementMatrix[3] = vector<int>(stdCards.size());
    for(int i = 0; i < 100; i++)
    {
        auto startMilli = chrono::steady_clock::now();
        randDeck.gdlevineRandomize();
        gdlevineRuntimesMatrix[3].push_back(chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - startMilli).count());

        for(int j = 0; j < randDeck.getItems().size(); j++)
        {
            gdlevineItemsPlacementMatrix[3][j] += randDeck.getItemsNewPosByOldIndex()[j];
        }
    }
    cout << "Done." << endl;
    // Test with a small deck.
    vector<Card> smallCards;
    smallCards.push_back(Card(Card::ace, Card::clubs, 0));
    smallCards.push_back(Card(Card::king, Card::clubs, 1));
    smallCards.push_back(Card(Card::three, Card::diamonds, 2));
    smallCards.push_back(Card(Card::jack, Card::diamonds, 3));
    smallCards.push_back(Card(Card::five, Card::hearts, 4));
    smallCards.push_back(Card(Card::ten, Card::hearts, 5));
    smallCards.push_back(Card(Card::seven, Card::spades, 6));
    smallCards.push_back(Card(Card::eight, Card::spades, 7));
    cout << "Testing gdlevineRandomize with a small deck (and gathering data, which takes the bulk of the time)..." << endl;
    gdlevineItemsPlacementMatrix[4] = vector<int>(smallCards.size());
    for(int i = 0; i < 100; i++)
    {
        Collection<Card> smallDeck;
        smallDeck.setItems(smallCards);

        auto startMilli = chrono::steady_clock::now();
        smallDeck.gdlevineRandomize();
        gdlevineRuntimesMatrix[4].push_back(chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - startMilli).count());

        for(int j = 0; j < smallDeck.getItems().size(); j++)
        {
            gdlevineItemsPlacementMatrix[4][j] += smallDeck.getItemsNewPosByOldIndex()[j];
        }
    }
    cout << "Done." << endl;
    // Test with a sorted deck.
    Collection<Card> tempDeckSmall;
    tempDeckSmall.setItems(smallCards);
    tempDeckSmall.sort();
    vector<Card> sortedCardsSmall = tempDeckSmall.getItems();
    cout << "Testing gdlevineRandomize with a small sorted deck (and gathering data, which takes the bulk of the time)..." << endl;
    gdlevineItemsPlacementMatrix[5] = vector<int>(sortedCardsSmall.size());
    for(int i = 0; i < 100; i++)
    {
        Collection<Card> sortedDeckSmall;
        sortedDeckSmall.setItems(sortedCardsSmall);

        auto startMilli = chrono::steady_clock::now();
        sortedDeckSmall.gdlevineRandomize();
        gdlevineRuntimesMatrix[5].push_back(chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - startMilli).count());

        for(int j = 0; j < sortedDeckSmall.getItems().size(); j++)
        {
            gdlevineItemsPlacementMatrix[5][j] += sortedDeckSmall.getItemsNewPosByOldIndex()[j];
        }
    }
    cout << "Done." << endl;
    // Test with a sorted deck in reverse order.
    reverse(sortedCardsSmall.begin(), sortedCardsSmall.end());
    cout << "Testing gdlevineRandomize with a small sorted deck in reverse order (and gathering data, which takes the bulk of the time)..." << endl;
    gdlevineItemsPlacementMatrix[6] = vector<int>(sortedCardsSmall.size());
    for(int i = 0; i < 100; i++)
    {
        Collection<Card> reversedDeckSmall;
        reversedDeckSmall.setItems(sortedCardsSmall);

        auto startMilli = chrono::steady_clock::now();
        reversedDeckSmall.gdlevineRandomize();
        gdlevineRuntimesMatrix[6].push_back(chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - startMilli).count());

        for(int j = 0; j < reversedDeckSmall.getItems().size(); j++)
        {
            gdlevineItemsPlacementMatrix[6][j] += reversedDeckSmall.getItemsNewPosByOldIndex()[j];
        }
    }
    cout << "Done." << endl;
    // Test with already-random decks.
    Collection<Card> randDeckSmall;
    randDeckSmall.setItems(smallCards);
    randDeckSmall.gdlevineRandomize();
    cout << "Testing gdlevineRandomize with small already-random decks (and gathering data, which takes the bulk of the time)..." << endl;
    gdlevineItemsPlacementMatrix[7] = vector<int>(smallCards.size());
    for(int i = 0; i < 100; i++)
    {
        auto startMilli = chrono::steady_clock::now();
        randDeckSmall.gdlevineRandomize();
        gdlevineRuntimesMatrix[7].push_back(chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - startMilli).count());

        for(int j = 0; j < randDeckSmall.getItems().size(); j++)
        {
            gdlevineItemsPlacementMatrix[7][j] += randDeckSmall.getItemsNewPosByOldIndex()[j];
        }
    }
    cout << "Done." << endl;
    // Test with a large deck.
    vector<Card> largeCards;
    for(int i = 0; i < 100; i++)
    {
        largeCards.insert(largeCards.end(), stdCards.begin(), stdCards.end());
    }
    for(int i = 52; i < largeCards.size(); i++)
    {
        largeCards[i].setDeckPos(i);
    }
    cout << "Testing gdlevineRandomize with a large deck (and gathering data, which takes the bulk of the time)..." << endl;
    gdlevineItemsPlacementMatrix[8] = vector<int>(largeCards.size());
    for(int i = 0; i < 100; i++)
    {
        Collection<Card> largeDeck;
        largeDeck.setItems(largeCards);

        auto startMilli = chrono::steady_clock::now();
        largeDeck.gdlevineRandomize();
        gdlevineRuntimesMatrix[8].push_back(chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - startMilli).count());

        for(int j = 0; j < largeDeck.getItems().size(); j++)
        {
            gdlevineItemsPlacementMatrix[8][j] += largeDeck.getItemsNewPosByOldIndex()[j];
        }
    }
    cout << "Done." << endl;
    // Test with a sorted deck.
    Collection<Card> tempDeckLarge;
    tempDeckLarge.setItems(largeCards);
    tempDeckLarge.sort();
    vector<Card> sortedCardsLarge = tempDeckLarge.getItems();
    cout << "Testing gdlevineRandomize with a large sorted deck (and gathering data, which takes the bulk of the time)..." << endl;
    gdlevineItemsPlacementMatrix[9] = vector<int>(sortedCardsLarge.size());
    for(int i = 0; i < 100; i++)
    {
        Collection<Card> sortedDeckLarge;
        sortedDeckLarge.setItems(sortedCardsLarge);

        auto startMilli = chrono::steady_clock::now();
        sortedDeckLarge.gdlevineRandomize();
        gdlevineRuntimesMatrix[9].push_back(chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - startMilli).count());

        for(int j = 0; j < sortedDeckLarge.getItems().size(); j++)
        {
            gdlevineItemsPlacementMatrix[9][j] += sortedDeckLarge.getItemsNewPosByOldIndex()[j];
        }
    }
    cout << "Done." << endl;
    // Test with a sorted deck in reverse order.
    reverse(sortedCardsLarge.begin(), sortedCardsLarge.end());
    cout << "Testing gdlevineRandomize with a large sorted deck in reverse order (and gathering data, which takes the bulk of the time)..." << endl;
    gdlevineItemsPlacementMatrix[10] = vector<int>(sortedCardsLarge.size());
    for(int i = 0; i < 100; i++)
    {
        Collection<Card> reversedDeckLarge;
        reversedDeckLarge.setItems(sortedCardsLarge);

        auto startMilli = chrono::steady_clock::now();
        reversedDeckLarge.gdlevineRandomize();
        gdlevineRuntimesMatrix[10].push_back(chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - startMilli).count());

        for(int j = 0; j < reversedDeckLarge.getItems().size(); j++)
        {
            gdlevineItemsPlacementMatrix[10][j] += reversedDeckLarge.getItemsNewPosByOldIndex()[j];
        }
    }
    cout << "Done." << endl;
    // Test with already-random decks.
    Collection<Card> randDeckLarge;
    randDeckLarge.setItems(largeCards);
    randDeckLarge.gdlevineRandomize();
    cout << "Testing gdlevineRandomize with large already-random decks (and gathering data, which takes the bulk of the time)..." << endl;
    gdlevineItemsPlacementMatrix[11] = vector<int>(largeCards.size());
    for(int i = 0; i < 100; i++)
    {
        auto startMilli = chrono::steady_clock::now();
        randDeckLarge.gdlevineRandomize();
        gdlevineRuntimesMatrix[11].push_back(chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - startMilli).count());

        for(int j = 0; j < randDeckLarge.getItems().size(); j++)
        {
            gdlevineItemsPlacementMatrix[11][j] += randDeckLarge.getItemsNewPosByOldIndex()[j];
        }
    }
    cout << "Done." << endl;
    cout << endl;

    // Display Results
    // gdlevineRandomize Runtimes
    cout << "gdlevineRandomize runtimes:" << endl << endl;
    // Standard-Sized Decks
    cout << "Standard-Sized Decks:" << endl;
    // Standard Deck
    cout << "Standard Deck:" << endl;
    cout << "Best-Case: " << *min_element(gdlevineRuntimesMatrix[0].begin(), gdlevineRuntimesMatrix[0].end()) << ", ";
    cout << "Worst-Case: " << *max_element(gdlevineRuntimesMatrix[0].begin(), gdlevineRuntimesMatrix[0].end()) << ", ";
    cout << "Average-Case: " << accumulate(gdlevineRuntimesMatrix[0].begin(), gdlevineRuntimesMatrix[0].end(), 0) * 1.0 / gdlevineRuntimesMatrix[0].size() << endl;
    // Sorted Deck
    cout << "Sorted Deck:" << endl;
    cout << "Best-Case: " << *min_element(gdlevineRuntimesMatrix[1].begin(), gdlevineRuntimesMatrix[1].end()) << ", ";
    cout << "Worst-Case: " << *max_element(gdlevineRuntimesMatrix[1].begin(), gdlevineRuntimesMatrix[1].end()) << ", ";
    cout << "Average-Case: " << accumulate(gdlevineRuntimesMatrix[1].begin(), gdlevineRuntimesMatrix[1].end(), 0) * 1.0 / gdlevineRuntimesMatrix[1].size() << endl;
    // Reversed Deck
    cout << "Reversed Deck:" << endl;
    cout << "Best-Case: " << *min_element(gdlevineRuntimesMatrix[2].begin(), gdlevineRuntimesMatrix[2].end()) << ", ";
    cout << "Worst-Case: " << *max_element(gdlevineRuntimesMatrix[2].begin(), gdlevineRuntimesMatrix[2].end()) << ", ";
    cout << "Average-Case: " << accumulate(gdlevineRuntimesMatrix[2].begin(), gdlevineRuntimesMatrix[2].end(), 0) * 1.0 / gdlevineRuntimesMatrix[2].size() << endl;
    // Randomized Deck
    cout << "Randomized Deck:" << endl;
    cout << "Best-Case: " << *min_element(gdlevineRuntimesMatrix[3].begin(), gdlevineRuntimesMatrix[3].end()) << ", ";
    cout << "Worst-Case: " << *max_element(gdlevineRuntimesMatrix[3].begin(), gdlevineRuntimesMatrix[3].end()) << ", ";
    cout << "Average-Case: " << accumulate(gdlevineRuntimesMatrix[3].begin(), gdlevineRuntimesMatrix[3].end(), 0) * 1.0 / gdlevineRuntimesMatrix[3].size() << endl << endl;
    // Small Decks
    cout << "Small Decks:" << endl;
    // Standard Deck
    cout << "Standard Deck:" << endl;
    cout << "Best-Case: " << *min_element(gdlevineRuntimesMatrix[4].begin(), gdlevineRuntimesMatrix[4].end()) << ", ";
    cout << "Worst-Case: " << *max_element(gdlevineRuntimesMatrix[4].begin(), gdlevineRuntimesMatrix[4].end()) << ", ";
    cout << "Average-Case: " << accumulate(gdlevineRuntimesMatrix[4].begin(), gdlevineRuntimesMatrix[4].end(), 0) * 1.0 / gdlevineRuntimesMatrix[4].size() << endl;
    // Sorted Deck
    cout << "Sorted Deck:" << endl;
    cout << "Best-Case: " << *min_element(gdlevineRuntimesMatrix[5].begin(), gdlevineRuntimesMatrix[5].end()) << ", ";
    cout << "Worst-Case: " << *max_element(gdlevineRuntimesMatrix[5].begin(), gdlevineRuntimesMatrix[5].end()) << ", ";
    cout << "Average-Case: " << accumulate(gdlevineRuntimesMatrix[5].begin(), gdlevineRuntimesMatrix[5].end(), 0) * 1.0 / gdlevineRuntimesMatrix[5].size() << endl;
    // Reversed Deck
    cout << "Reversed Deck:" << endl;
    cout << "Best-Case: " << *min_element(gdlevineRuntimesMatrix[6].begin(), gdlevineRuntimesMatrix[6].end()) << ", ";
    cout << "Worst-Case: " << *max_element(gdlevineRuntimesMatrix[6].begin(), gdlevineRuntimesMatrix[6].end()) << ", ";
    cout << "Average-Case: " << accumulate(gdlevineRuntimesMatrix[6].begin(), gdlevineRuntimesMatrix[6].end(), 0) * 1.0 / gdlevineRuntimesMatrix[6].size() << endl;
    // Randomized Deck
    cout << "Randomized Deck:" << endl;
    cout << "Best-Case: " << *min_element(gdlevineRuntimesMatrix[7].begin(), gdlevineRuntimesMatrix[7].end()) << ", ";
    cout << "Worst-Case: " << *max_element(gdlevineRuntimesMatrix[7].begin(), gdlevineRuntimesMatrix[7].end()) << ", ";
    cout << "Average-Case: " << accumulate(gdlevineRuntimesMatrix[7].begin(), gdlevineRuntimesMatrix[7].end(), 0) * 1.0 / gdlevineRuntimesMatrix[7].size() << endl << endl;
    // Large Decks
    cout << "Large Decks:" << endl;
    // Standard Deck
    cout << "Standard Deck:" << endl;
    cout << "Best-Case: " << *min_element(gdlevineRuntimesMatrix[8].begin(), gdlevineRuntimesMatrix[8].end()) << ", ";
    cout << "Worst-Case: " << *max_element(gdlevineRuntimesMatrix[8].begin(), gdlevineRuntimesMatrix[8].end()) << ", ";
    cout << "Average-Case: " << accumulate(gdlevineRuntimesMatrix[8].begin(), gdlevineRuntimesMatrix[8].end(), 0) * 1.0 / gdlevineRuntimesMatrix[8].size() << endl;
    // Sorted Deck
    cout << "Sorted Deck:" << endl;
    cout << "Best-Case: " << *min_element(gdlevineRuntimesMatrix[9].begin(), gdlevineRuntimesMatrix[9].end()) << ", ";
    cout << "Worst-Case: " << *max_element(gdlevineRuntimesMatrix[9].begin(), gdlevineRuntimesMatrix[9].end()) << ", ";
    cout << "Average-Case: " << accumulate(gdlevineRuntimesMatrix[9].begin(), gdlevineRuntimesMatrix[9].end(), 0) * 1.0 / gdlevineRuntimesMatrix[9].size() << endl;
    // Reversed Deck
    cout << "Reversed Deck:" << endl;
    cout << "Best-Case: " << *min_element(gdlevineRuntimesMatrix[10].begin(), gdlevineRuntimesMatrix[10].end()) << ", ";
    cout << "Worst-Case: " << *max_element(gdlevineRuntimesMatrix[10].begin(), gdlevineRuntimesMatrix[10].end()) << ", ";
    cout << "Average-Case: " << accumulate(gdlevineRuntimesMatrix[10].begin(), gdlevineRuntimesMatrix[10].end(), 0) * 1.0 / gdlevineRuntimesMatrix[10].size() << endl;
    // Randomized Deck
    cout << "Randomized Deck:" << endl;
    cout << "Best-Case: " << *min_element(gdlevineRuntimesMatrix[11].begin(), gdlevineRuntimesMatrix[11].end()) << ", ";
    cout << "Worst-Case: " << *max_element(gdlevineRuntimesMatrix[11].begin(), gdlevineRuntimesMatrix[11].end()) << ", ";
    cout << "Average-Case: " << accumulate(gdlevineRuntimesMatrix[11].begin(), gdlevineRuntimesMatrix[11].end(), 0) * 1.0 / gdlevineRuntimesMatrix[11].size() << endl << endl;
    // gdlevineRandomize items' new-position indexes distributions:
    cout << "gdlevineRandomize items' new-position indexes distributions:" << endl << endl;
    // Standard-Sized Decks
    cout << "Standard-Sized Decks:" << endl;
    // Standard Deck
    cout << "Standard Deck:" << endl << gdlevineItemsPlacementMatrix[0][0];
    for(int i = 1; i < gdlevineItemsPlacementMatrix[0].size(); i++)
    {
        cout << ", " << gdlevineItemsPlacementMatrix[0][i];
    }
    cout << endl;
    // Sorted Deck
    cout << "Sorted Deck:" << endl << gdlevineItemsPlacementMatrix[1][0];
    for(int i = 1; i < gdlevineItemsPlacementMatrix[1].size(); i++)
    {
        cout << ", " << gdlevineItemsPlacementMatrix[1][i];
    }
    cout << endl;
    // Reversed Deck
    cout << "Reversed Deck:" << endl << gdlevineItemsPlacementMatrix[2][0];
    for(int i = 1; i < gdlevineItemsPlacementMatrix[2].size(); i++)
    {
        cout << ", " << gdlevineItemsPlacementMatrix[2][i];
    }
    cout << endl;
    // Randomized Deck
    cout << "Randomized Deck:" << endl << gdlevineItemsPlacementMatrix[3][0];
    for(int i = 1; i < gdlevineItemsPlacementMatrix[3].size(); i++)
    {
        cout << ", " << gdlevineItemsPlacementMatrix[3][i];
    }
    cout << endl << endl;
    // Small Decks
    cout << "Small Decks:" << endl;
    // Standard Deck
    cout << "Standard Deck:" << endl << gdlevineItemsPlacementMatrix[4][0];
    for(int i = 1; i < gdlevineItemsPlacementMatrix[4].size(); i++)
    {
        cout << ", " << gdlevineItemsPlacementMatrix[4][i];
    }
    cout << endl;
    // Sorted Deck
    cout << "Sorted Deck:" << endl << gdlevineItemsPlacementMatrix[5][0];
    for(int i = 1; i < gdlevineItemsPlacementMatrix[5].size(); i++)
    {
        cout << ", " << gdlevineItemsPlacementMatrix[5][i];
    }
    cout << endl;
    // Reversed Deck
    cout << "Reversed Deck:" << endl << gdlevineItemsPlacementMatrix[6][0];
    for(int i = 1; i < gdlevineItemsPlacementMatrix[6].size(); i++)
    {
        cout << ", " << gdlevineItemsPlacementMatrix[6][i];
    }
    cout << endl;
    // Randomized Deck
    cout << "Randomized Deck:" << endl << gdlevineItemsPlacementMatrix[7][0];
    for(int i = 1; i < gdlevineItemsPlacementMatrix[7].size(); i++)
    {
        cout << ", " << gdlevineItemsPlacementMatrix[7][i];
    }
    cout << endl << endl;
    // Large Decks
    cout << "Large Decks:" << endl;
    // Standard Deck
    cout << "Standard Deck:" << endl << gdlevineItemsPlacementMatrix[8][0];
    for(int i = 1; i < gdlevineItemsPlacementMatrix[8].size(); i++)
    {
        cout << ", " << gdlevineItemsPlacementMatrix[8][i];
    }
    cout << endl;
    // Sorted Deck
    cout << "Sorted Deck:" << endl << gdlevineItemsPlacementMatrix[9][0];
    for(int i = 1; i < gdlevineItemsPlacementMatrix[9].size(); i++)
    {
        cout << ", " << gdlevineItemsPlacementMatrix[9][i];
    }
    cout << endl;
    // Reversed Deck
    cout << "Reversed Deck:" << endl << gdlevineItemsPlacementMatrix[10][0];
    for(int i = 1; i < gdlevineItemsPlacementMatrix[10].size(); i++)
    {
        cout << ", " << gdlevineItemsPlacementMatrix[10][i];
    }
    cout << endl;
    // Randomized Deck
    cout << "Randomized Deck:" << endl << gdlevineItemsPlacementMatrix[11][0];
    for(int i = 1; i < gdlevineItemsPlacementMatrix[11].size(); i++)
    {
        cout << ", " << gdlevineItemsPlacementMatrix[11][i];
    }
    cout << endl;

    return 0;
}
