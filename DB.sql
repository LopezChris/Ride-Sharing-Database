drop database if exists SJSUber;
create database SJSUber;
use SJSUber;

CREATE TABLE user(
	SJSU_ID		CHAR(9)			NOT NULL 	UNIQUE,
    EMAIL		VARCHAR(50) 	NOT NULL 	UNIQUE,
    USER_NAME	VARCHAR(25)		NOT NULL 	UNIQUE,
    ADDRESS		VARCHAR(50)		NOT NULL,
    NAME		VARCHAR(50)		NOT NULL,
    PASSWORD	VARCHAR(25)		NOT NULL,
    USER_TYPE	VARCHAR(10)		NOT NULL,
    ANSWER_SQ1	VARCHAR(50)		NOT NULL,
    ANSWER_SQ2	VARCHAR(50)		NOT NULL,
    PRIMARY KEY(SJSU_ID)
);

CREATE TABLE driver(
	LICENSE_NUM	CHAR(9)			NOT NULL	 	UNIQUE,
    SJID		CHAR(9)			NOT NULL,
    EXP_DATE	CHAR(8)			NOT NULL,
    PRIMARY KEY(LICENSE_NUM),
    FOREIGN KEY (SJID) REFERENCES user (SJSU_ID)
);

CREATE TABLE cars(
	LIC_NUM		CHAR(9)			NOT NULL		UNIQUE,
    REG_NUM		CHAR(9)			NOT NULL		UNIQUE,
    INSURANCE	VARCHAR(25)		NOT NULL,
	MAX_SEATS	CHAR(1)			NOT NULL,
	MODEL		VARCHAR(25)		NOT NULL,
	MAKE		VARCHAR(25)		NOT NULL,
    PRIMARY KEY(REG_NUM),
    FOREIGN KEY (LIC_NUM) REFERENCES driver (LICENSE_NUM)
);

CREATE TABLE route(
	ROUTE_ID	CHAR(9)			NOT NULL	 	UNIQUE,
    CREATED_ON	CHAR(10)		NOT NULL,
	DEPART_TIME	CHAR(8)			NOT NULL,
	SHORTEST_DIST	CHAR(2)		NOT NULL,
	START_LOC	VARCHAR(100)	NOT NULL,
	END_LOC		VARCHAR(100)	NOT NULL,
    PRIMARY KEY(ROUTE_ID)
);

CREATE TABLE stop(
	STOP_ID		CHAR(9)				NOT NULL	UNIQUE,
    PICKUP_LOC	VARCHAR(100)		NOT NULL,
	DROPOFF_LOC	VARCHAR(100)		NOT NULL,
	STOP_CREATED_ON	CHAR(10)		NOT NULL,
	STOP_DEPART_TIME CHAR(8)		NOT NULL,
    PRIMARY KEY(STOP_ID)
);

CREATE TABLE has2(
	RTE_ID		CHAR(9)			NOT NULL,
    STP_ID		CHAR(9)			NOT NULL,
	PRIMARY KEY (STP_ID),
    FOREIGN KEY (RTE_ID) REFERENCES	route	(ROUTE_ID),
	FOREIGN KEY	(STP_ID) REFERENCES	stop	(STOP_ID)
);

CREATE TABLE has1(
	L_NUM		CHAR(9)			NOT NULL,
    RTE_ID		CHAR(9)			NOT NULL,
    PRIMARY KEY (L_NUM),
    FOREIGN KEY (L_NUM)	REFERENCES	driver	(LICENSE_NUM),
	FOREIGN KEY	(RTE_ID) REFERENCES	route	(ROUTE_ID)
);


CREATE TABLE request(
	REQUEST_ID	CHAR(9)				NOT NULL	UNIQUE,
    SEATS_REQST	CHAR(1)				NOT NULL,
    DEPART_TIME	CHAR(8)				NOT NULL,
    CREATED_ON	CHAR(10)			NOT NULL,
    START_LOC	VARCHAR(100)		NOT NULL,
    END_LOC		VARCHAR(100)		NOT NULL,
    PRIMARY KEY	(REQUEST_ID)
);


CREATE TABLE makes(
	SJ_ID		CHAR(9)			NOT NULL,
    REQ_ID		CHAR(9)			NOT NULL,
    PRIMARY KEY	(SJ_ID),
    FOREIGN KEY	(SJ_ID)		REFERENCES user	(SJSU_ID),
    FOREIGN KEY	(REQ_ID)	REFERENCES request	(REQUEST_ID)
);

CREATE TABLE matches(
	RT_ID		CHAR(9)			NOT NULL,
    RQUST_ID	CHAR(9)			NOT NULL,
    ACCPT_REJ	CHAR(1),
    PRIMARY KEY	(RT_ID),
	FOREIGN KEY	(RT_ID)	REFERENCES	route	(ROUTE_ID),
    FOREIGN KEY	(RQUST_ID)	REFERENCES request	(REQUEST_ID)
);


insert into user values('103034004', 'Moira.Nickel@sjsu.edu', 'fossashriek', '5 Myers Dr. Yakima, WA 98908', ' Moira Nickel', 'GeZJuzAe', 'Staff', ' Squint', 'Spot');
insert into user values('159030021', 'Fatima.Hauck@sjsu.edu', 'dovestechnician', '9172 Manor Station St. Massillon, OH 44646', ' Fatima Hauck', 'JuZLFXDX', 'Staff', ' Mila', 'Marshmallow');
insert into user values('393807492', 'Ghislaine.Rolan@gmail.com', 'passionaterack', '268 Main St. Clinton, MD 20735', ' Ghislaine Rolan', 'JdhtSXn5', 'Student', ' Grace', 'Precious');
insert into user values('517837321', 'Clarice.Monterroso@sjsu.edu', 'washboardbulwark', '400 College Street Temple Hills, MD 20748', ' Clarice Monterroso', '7HedKZnj', 'Professor', ' Marble', 'Yogi');
insert into user values('344585989', 'Leonarda.Cronan@gmail.com', 'bicyclinggratis', '9095 Lyme St.Helotes, TX 78023', ' Leonarda Cronan', 'Lzmc6CQE', 'Staff', ' Darth', 'Glacier');
insert into user values('441969669', 'Fausto.Sturm@sjsu.edu', 'fitswary', '15 Sheffield Ave.Nottingham, MD 21236', ' Fausto Sturm', '37w5Qwet', 'Student', ' Dunk', 'Katrina');
insert into user values('437313975', 'Dillon.Coons@sjsu.edu', 'herdleader', '9703 Thorne Drive Hollywood, FL 33020', ' Dillon Coons', 'vLjx4MLT', 'Student', ' Jeter', 'Sponge');
insert into user values('337336841', 'Darby.Otterson@sjsu.edu', 'garboardcrocodiles', '329 Swanson Ave. San Angelo, TX 76901', ' Darby Otterson', '4Kd639KC', 'Student', ' Alvin', 'Charm');
insert into user values('255505419', 'Ruthe.Gilyard@sjsu.edu', 'wenchplatelet', '7168 S. Ridgeview St. Little Rock, AR 72209', ' Ruthe Gilyard', 'QFAgWWgV', 'Student', ' Dusty', 'Irie');
insert into user values('563608587', 'Harland.Blasingame@sjsu.edu', 'marchedhole', '8083 Lilac Street Nanuet, NY 10954', ' Harland Blasingame', 'y9gE455s', 'Student', ' Mimi', 'Peter');


insert into driver values('564316931', '103034004', '0/3/20');
insert into driver values('296421122', '159030021', '1/4/21');
insert into driver values('227725570', '393807492', '2/5/22');
insert into driver values('367787270', '517837321', '3/6/23');
insert into driver values('962554631', '344585989', '4/7/24');
insert into driver values('855359750', '441969669', '5/8/25');
insert into driver values('147256585', '437313975', '6/9/26');
insert into driver values('199091719', '337336841', '7/10/27');
insert into driver values('663662857', '255505419', '8/11/28');
insert into driver values('434120715', '563608587', '9/12/29');


insert into cars values('564316931', '694658816', ' Geiko', '4', 'Civic', 'Honda');
insert into cars values('296421122', '111119361', ' AAA', '4', 'Corolla', 'Toyota');
insert into cars values('227725570', '652943365', ' Allstate', '4', 'Santa Fe', 'Hunday');
insert into cars values('367787270', '415098117', ' Farmers', '4', 'Regal', 'Buick');
insert into cars values('962554631', '430196231', ' Geiko', '4', 'Metro', 'Geo');
insert into cars values('855359750', '249418758', ' Geiko', '4', 'Diablo', 'Lamborghini');
insert into cars values('147256585', '638245128', ' AAA', '4', 'Elise', 'Lotus');
insert into cars values('199091719', '289226250', ' Allstate', '4', 'Accord', 'Honda');
insert into cars values('663662857', '410011144', ' Farmers', '4', 'FR-S', 'Scion');
insert into cars values('434120715', '930141961', ' Geiko', '4', 'Wrangler', 'Jeep');



insert into route values('534120707', '4/20/2019', '22', '1', 'home', 'SJSU');
insert into route values('641515524', '5/05/2018', '23', '2', 'home', 'SJSU');
insert into route values('926217477', '1/20/2018', '24', '3', 'home', 'SJSU');
insert into route values('748764677', '2/30/2018', '25', '4', 'home', 'SJSU');
insert into route values('216406278', '4/20/2018', '26', '5', 'home', 'SJSU');
insert into route values('630141959', '8/30/2017', '27', '6', 'home', 'SJSU');
insert into route values('604524296', '1/20/2019', '28', '7', 'home', 'SJSU');
insert into route values('380014856', '2/4/2018', '29', '8', 'home', 'SJSU');
insert into route values('692950794', '6/6/2018', '30', '9', 'home', 'SJSU');
insert into route values('557521930', '1/1/2011', '31', '10', 'home', 'SJSU');


insert into stop values('261846273', '5 Myers Dr. Yakima, WA 98908', 'SJSU', '4/20/2019', 'Fri Apr 27 12:52:57 2018');
insert into stop values('688118018', '9172 Manor Station St. Massillon, OH 44646', 'SJSU', '5/05/2018',  'Fri Apr 27 12:52:57 2018');
insert into stop values('168841219', '268 Main St. Clinton, MD 20735', 'SJSU', '1/20/2018',  'Fri Apr 27 12:52:57 2018');
insert into stop values('530890428', '400 College Street Temple Hills, MD 20748', 'SJSU', '2/30/2018',  'Fri Apr 27 12:52:57 2018');
insert into stop values('684431350', '9095 Lyme St.Helotes, TX 78023', 'SJSU', '4/20/2018', 'Fri Apr 27 12:52:57 2018');
insert into stop values('543532039', '15 Sheffield Ave.Nottingham, MD 21236', 'SJSU', '8/30/2017',  'Fri Apr 27 12:52:57 2018');
insert into stop values('271511816', '9703 Thorne Drive Hollywood, FL 33020', 'SJSU', '1/20/2019', 'Fri Apr 27 12:52:57 2018');
insert into stop values('300854025', '329 Swanson Ave. San Angelo, TX 76901', 'SJSU', '2/4/2018',  'Fri Apr 27 12:52:57 2018');
insert into stop values('506486539', '7168 S. Ridgeview St. Little Rock, AR 72209', 'SJSU', '6/6/2018',  'Fri Apr 27 12:52:57 2018');
insert into stop values('900199948', '8083 Lilac Street Nanuet, NY 10954', 'SJSU', '1/1/2011',  'Fri Apr 27 12:52:57 2018');




insert into has1 values('564316931', '534120707');
insert into has1 values('296421122', '641515524');
insert into has1 values('227725570', '926217477');
insert into has1 values('367787270', '748764677');
insert into has1 values('962554631', '216406278');
insert into has1 values('855359750', '630141959');
insert into has1 values('147256585', '604524296');
insert into has1 values('199091719', '380014856');
insert into has1 values('663662857', '692950794');
insert into has1 values('434120715', '557521930');


insert into has2 values('534120707', '261846273');
insert into has2 values('641515524', '688118018');
insert into has2 values('926217477', '168841219');
insert into has2 values('748764677', '530890428');
insert into has2 values('216406278', '684431350');
insert into has2 values('630141959', '543532039');
insert into has2 values('604524296', '271511816');
insert into has2 values('380014856', '300854025');
insert into has2 values('692950794', '506486539');
insert into has2 values('557521930', '900199948');




select *
from driver inner join user
where driver.SJID = user.SJSU_ID 
and driver.EXP_DATE = ' 2/5/22';


