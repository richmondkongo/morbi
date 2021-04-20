BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS "championnat" (
	"id_chp"	INTEGER,
	"libelle"	TEXT,
	"pays"	TEXT,
	"division"	TEXT,
	"saison"	TEXT,
	PRIMARY KEY("id_chp")
);
CREATE TABLE IF NOT EXISTS "equipe" (
	"id_eq"	INTEGER,
	"libelle"	TEXT,
	"id_chp"	INTEGER NOT NULL,
	PRIMARY KEY("id_eq"),
	FOREIGN KEY("id_chp") REFERENCES "championnat"("id_chp")
);
CREATE TABLE IF NOT EXISTS "rencontrer" (
	"id_ren"	INTEGER,
	"jour"	TEXT,
	"score_1"	INTEGER,
	"score_2"	INTEGER,
	"eq_2"	INTEGER,
	"eq_1"	INTEGER,
	"num_journee"	INTEGER,
	PRIMARY KEY("id_ren"),
	FOREIGN KEY("eq_1") REFERENCES "equipe"("id_eq"),
	FOREIGN KEY("eq_2") REFERENCES "equipe"("id_eq")
);
INSERT INTO "championnat" ("id_chp","libelle","pays","division","saison") VALUES (1,'ligua','espagne','1','2021');
INSERT INTO "equipe" ("id_eq","libelle","id_chp") VALUES (1,'eq_A',1),
 (2,'eq_B',1),
 (3,'eq_C',1),
 (4,'eq_D',1);
INSERT INTO "rencontrer" ("id_ren","jour","score_1","score_2","eq_2","eq_1","num_journee") VALUES (1,'19/04/2021',0,0,2,1,1),
 (2,'20/04/2021',5,3,1,3,1),
 (3,'21/04/2021',0,2,4,1,1),
 (4,'22/04/2021',0,1,2,3,1),
 (5,'23/04/2021',0,0,2,4,1),
 (6,'24/04/2021',-1,-1,3,4,1);
COMMIT;
