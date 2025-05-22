-- User table
CREATE TABLE IF NOT EXISTS "User" (
    "UserId" SERIAL PRIMARY KEY,
    "Username" VARCHAR(50),
    "Password" VARCHAR(256),
    "Name" VARCHAR(50),
    "Surname" VARCHAR(50),
    "Email" VARCHAR(50),
    "ProfilePhoto" VARCHAR(255),
    "Online" BOOLEAN,
    "IntraLogin" BOOLEAN DEFAULT FALSE,
    "TwoFactorAuth" BOOLEAN DEFAULT FALSE,
    "CurrentLevel" INT DEFAULT 1
);

CREATE TABLE IF NOT EXISTS "Friend" (
    "FriendId" SERIAL PRIMARY KEY,
    "UserId" INT REFERENCES "User"("UserId"),
    "FriendUserId" INT REFERENCES "User"("UserId")
);

CREATE TABLE IF NOT EXISTS "FriendRequest" (
    "FriendRequestId" SERIAL PRIMARY KEY,
    "UserId" INT REFERENCES "User"("UserId"),
    "FriendUserId" INT REFERENCES "User"("UserId")
);
-- Player table, linked to User
CREATE TABLE IF NOT EXISTS "Player" (
    "PlayerId" SERIAL PRIMARY KEY,
    "UserId" INT REFERENCES "User"("UserId"),
    "History" INT,
    "Score" INT
);

-- History table
CREATE TABLE IF NOT EXISTS "History" (
    "HistoryId" SERIAL PRIMARY KEY,
    "DateTime" TIMESTAMP
);

-- Tournament table
CREATE TABLE IF NOT EXISTS "Tournament" (
    "TournamentId" SERIAL PRIMARY KEY,
    "Style" VARCHAR(50)
);

-- TournamentPlayer table, linking users to tournaments
CREATE TABLE IF NOT EXISTS "TournamentPlayer" (
    "TournamentPlayerId" SERIAL PRIMARY KEY,
    "TournamentId" INT REFERENCES "Tournament"("TournamentId"),
    "UserId" INT REFERENCES "User"("UserId")
);

-- MatchSystem table
CREATE TABLE IF NOT EXISTS "MatchSystem" (
    "MatchSystemId" SERIAL PRIMARY KEY,
    "Style" VARCHAR(50)
);

-- TournamentMatch table, linked to Tournament
CREATE TABLE IF NOT EXISTS "TournamentMatch" (
    "TournamentMatchId" SERIAL PRIMARY KEY,
    "TournamentId" INT REFERENCES "Tournament"("TournamentId"),
    "Stage" VARCHAR(50)
);

-- NormalMatch table
CREATE TABLE IF NOT EXISTS "NormalMatch" (
    "NormalMatchId" SERIAL PRIMARY KEY
);

-- MatchRelationship table if needed
CREATE TABLE IF NOT EXISTS "MatchRelationship" (
    "RelationshipId" SERIAL PRIMARY KEY,
    "MatchType" VARCHAR(50) CHECK ("MatchType" IN ('TournamentMatch', 'NormalMatch')),
    "MatchId" INT
);

-- ChatType table (defines types of chats)
CREATE TABLE IF NOT EXISTS "ChatType" (
    "ChatTypeId" SERIAL PRIMARY KEY,
    "TypeName" VARCHAR(20) CHECK ("TypeName" IN ('global', 'private', 'group'))
);
-- Chat table
CREATE TABLE IF NOT EXISTS "Chat" (
    "ChatId" SERIAL PRIMARY KEY,
    "ChatTypeId" INT REFERENCES "ChatType"("ChatTypeId"),
    "Name" VARCHAR(100), -- Optional for group chats
    "CreatedBy" INT REFERENCES "User"("UserId"), -- Creator of the group (optional for global/private)
    "CreatedAt" TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);


-- ChatUsers table (links users to chats)
CREATE TABLE IF NOT EXISTS "ChatUsers" (
    "ChatUserId" SERIAL PRIMARY KEY,
    "ChatId" INT REFERENCES "Chat"("ChatId") ON DELETE CASCADE,
    "UserId" INT REFERENCES "User"("UserId") ON DELETE CASCADE,
    "IsAdmin" BOOLEAN DEFAULT FALSE, -- For group chat admins
    "JoinedAt" TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Message table (stores chat messages)
CREATE TABLE IF NOT EXISTS "Message" (
    "MessageId" SERIAL PRIMARY KEY,
    "ChatId" INT REFERENCES "Chat"("ChatId") ON DELETE CASCADE,
    "SenderUserId" INT REFERENCES "User"("UserId") ON DELETE SET NULL,
    "Content" TEXT NOT NULL,
    "TimeStamp" TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Add the 'Global' type to ChatType
INSERT INTO "ChatType" ("TypeName") 
VALUES ('global')
ON CONFLICT DO NOTHING;

-- Add the global chat to the Chat table if it doesn't exist
DO $$
BEGIN
    IF NOT EXISTS (
        SELECT 1 
        FROM "Chat" c
        JOIN "ChatType" ct ON c."ChatTypeId" = ct."ChatTypeId"
        WHERE ct."TypeName" = 'global' AND c."Name" = 'Global Chat'
    ) THEN
        INSERT INTO "Chat" ("ChatTypeId", "Name")
        VALUES (
            (SELECT "ChatTypeId" FROM "ChatType" WHERE "TypeName" = 'global'),
            'Global Chat'
        );
    END IF;
END $$;