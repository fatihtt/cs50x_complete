SELECT songs.name AS name FROM songs
JOIN artists ON artists.ID = songs.artist_id
WHERE artists.name = "Post Malone"