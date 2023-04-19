SELECT AVG(energy) FROM songs
JOIN artists ON artists.ID = songs.artist_id
WHERE artists.name = "Drake"