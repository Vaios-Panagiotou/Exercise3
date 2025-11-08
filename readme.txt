#Αναφορά Εργασίας - Ομάδα 110

##👥 Ομάδα

-**Γιάννης Γρυπιώτης:** sdi2100028  
-**Βάιος Παναγιώτου:** sdi2100133  
-**Γιώργος Σκούρας:** sdi2100172

###🧑‍💻 Ποιος υλοποίησε τι

-**Chunk:** Γιάννης Γρυπιώτης (sdi2100028)  
-**Sort:** Βάιος Παναγιώτου (sdi2100133)  
-**Merge:** Γιώργος Σκούρας (sdi2100172)  
    -*Σημείωση:* Για το Merge, όπου υπήρχε πρόβλημα, υπήρχε συμβουλευτική υποστήριξη από την υπόλοιπη ομάδα. Όλη η ομάδα γνωρίζει τι γίνεται στο merge.

---

##🚀 Εκτέλεση

Για να φτιάξετε το εκτελέσιμο (δείχνει τις δυνατότητες της βιβλιοθήκης BF):

```bash
make sort
```

Για να τρέξετε το εκτελέσιμο:

```bash
./build/sort_main
```

---

## 📝 Σχεδιαστικές Επιλογές & Σημειώσεις

### SORT.c
- Η συνάρτηση ταξινόμησης που χρησιμοποιήθηκε είναι η Bubble Sort.

### CHUNK.c
- Δημιουργήθηκε global πίνακας CHUNKS και μεταβλητή μεγέθους για κεντρική διαχείριση των chunks.  
    - Αιτιολόγηση: προτιμήθηκε αυτή η λύση για να αποφευχθεί εξωτερική τροποποίηση των chunks, παρότι γενικά θεωρείται κακή πρακτική.
- MERGE.c  
    - Εφαρμόστηκε ο αλγόριθμος της διάλεξης για τη φάση συγχώνευσης.
- Χρήση ChatGPT  
    - Χρησιμοποιήθηκε κυρίως για ιδέες και διευκρινίσεις — περίπου 90% της υλοποίησης έγινε ανεξάρτητα.
- Έλεγχος & Δυσλειτουργίες  
    - Δοκιμάστηκε με 5000 εγγραφές και λειτούργησε σωστά. Υπάρχει προγραμματισμένο προειδοποιητικό μήνυμα που μπορεί να αφαιρεθεί ή να σχολιαστεί.
- Υπάρχει ένα προγραμματισμένο μήνυμα "λάθους" για ασφάλεια στην εκτέλεση — μπορεί να αφαιρεθεί ή να γίνει σχόλιο.

---

## 🔧 Λεπτομέρειες Υλοποίησης

1. CHUNK.C / CHUNK.H
     - Δομές
         - `CHUNK` — αφέθηκε όπως ήταν.
         - `CHUNK_Iterator` — αποθηκεύει το file descriptor και έναν ακέραιο που δείχνει σε ποιο chunk βρίσκομαι.
     - Συναρτήσεις (Βοηθητικές)
         - `void SetCHUNK(int from_BlockId, int to_BlockId, int recordsInChunk, int blocksInChunk, CHUNK *chunkModified)`  
             Αποθηκεύει τις μεταβλητές στο δοθέν CHUNK.
         - `int Arraysize()`  
             Επιστρέφει πόσα chunks έχουν δημιουργηθεί.
         - `void Delete_Chunk_Array()`  
             Απελευθερώνει δυναμικά δεσμευμένο χώρο για τον πίνακα με τα chunks (πρέπει να καλείται για αποφυγή memory leaks).
     - Υπάρχουσες (Υλοποιημένες)
         - `CHUNK_Iterator CHUNK_CreateIterator(int fileDesc, int blocksInChunk)`  
             Υπολογίζει πόσα CHUNKS χρειάζονται, αρχικοποιεί iterator, δεσμεύει χώρο και αρχικοποιεί κάθε CHUNK (ειδική μεταχείριση για το τελευταίο).
         - `int CHUNK_GetNext(CHUNK_Iterator *iterator, CHUNK* chunk)`  
             Επιστρέφει το επόμενο CHUNK ή μήνυμα λάθους αν είναι το τελευταίο (επιστρέφει 1 για αποτυχία, 0 για επιτυχία).
         - `CHUNK_RecordIterator CHUNK_CreateRecordIterator(CHUNK *chunk)`  
             Αρχικοποιεί iterator εγγραφών για το CHUNK.
         - `int CHUNK_GetNextRecord(CHUNK_RecordIterator *iterator, Record* record)`  
             Επιστρέφει την επόμενη εγγραφή ή 1 για fail, 0 για success.
         - `void CHUNK_Print(CHUNK chunk)`  
             Χρησιμοποιεί Record Iterator και εκτυπώνει τα περιεχόμενα του CHUNK.
         - `int CHUNK_GetIthRecordInChunk(CHUNK* chunk, int i, Record* record)`  
             Ελέγχει όρια, βρίσκει block & θέση, παίρνει την εγγραφή, κάνει unpin και επιστρέφει 0/1.
         - `int CHUNK_UpdateIthRecord(CHUNK* chunk, int i, Record record)`  
             Παρόμοια με την Get αλλά ενημερώνει την εγγραφή.

2. SORT.C
     - `shouldSwap(Record* rec1, Record* rec2)`  
         Συγκρίνει με `strcmp` πρώτα `name`, μετά `surname`. Χρησιμοποιείται για να αποφασίσει αν πρέπει να γίνει ανταλλαγή.
     - `sort_FileInChunks(int fileDesc, int blocksInChunk, int bWay)`  
         Δημιουργεί `CHUNK_Iterator`, παίρνει κάθε chunk με `CHUNK_GetNext` και καλεί `sort_Chunk`.
     - `sort_Chunk(int fileDesc, CHUNK* chunk)`  
         Υλοποιεί Bubble Sort. Παίρνει εγγραφές με:
         - `CHUNK_GetIthRecordInChunk(chunk, j + 1, &record1);`
         - `CHUNK_GetIthRecordInChunk(chunk, j + 2, &record2);`  
         Συγκρίνει με `shouldSwap` και ανταλλάσσει αν χρειάζεται.

3. MERGE.C
     - Σημείωση: Ο πίνακας `recordsInChunk` δεν επηρεάζει το αποτέλεσμα.
     - `merge(int fileDesc, int blocksInChunk, int bWay, int out_fileDesc)`  
         Υλοποιεί τη φάση συγχώνευσης. Υπολογίζει πόσα loops χρειάζονται για συγχώνευση με `bWay` chunks, χειρίζεται ειδική περίπτωση για το τελευταίο loop.
         - Χρησιμοποιείται πίνακας εγγραφών (μία θέση ανά chunk) με αρχική τιμή `NOT_FOUND` για `record_id`.
         - Με τον πίνακα αυτόν και με `Chunk_Iterator` βρίσκουμε κάθε φορά την μικρότερη εγγραφή.
     - `findSmallestRecord(...)`  
         Βρίσκει τη μικρότερη εγγραφή χρησιμοποιώντας `shouldSwap`.
     - `IsEmpty(Record* records, int size)`  
         Ελέγχει αν όλα τα `record_id` είναι `NOT_FOUND`.

4. MAIN()
     - Κάνει `sort` στα αρχεία, μετά `merge` και τα εκτυπώνει.
     - Το όνομα του αρχείου αποθηκεύεται σε global μεταβλητή για τις εκτυπώσεις.

---

## 🔗 Σύνδεσμοι ChatGPT
- Merge:
    - https://chat.openai.com/share/d735eb05-2231-49b2-981a-6e8456a39a67
    - https://chat.openai.com/share/61c4fd96-8675-4030-9708-7ca12e266ac4
- Chunk:
    - https://chat.openai.com/share/c3f5d4b1-a81c-421f-87dd-5867a69baa36
    - https://chat.openai.com/share/afc45fef-d08d-4d6b-a32e-0020f88d88e1
    - https://chat.openai.com/share/a69376bc-a61c-460c-804a-1a13a7bb505d
