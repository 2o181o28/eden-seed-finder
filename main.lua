local finder = RegisterMod("Eden Seed Finder", 1)

local r = false
local kill = true
local current = 1
local seeds_list = {
"B82T 2ZSB",
"B6J6 WY0A",
"BVBY TZ78",
"B02S YK7L",
"BY1B LBFP",
"BX6T YFAA",
"BW1B WK9K",
"BT44 NBJE",
"BR4M 1TJC",
"BQDK T8SJ",
"BM69 1GKW",
"BLW9 WWVE",
"BKJR RYX9",
"BJDJ 1FLL",
"BHXB 4RWT",
"BF03 6Q8L",
"BF8M 706L",
"BFEL VLXK",
"BFPA BX02",
"BEY4 SKS4",
"A938 JPJY",
"A8YS 6LJ9",
"A7P2 VGHE",
"A6WZ 1QAB",
"AVD0 KJGH",
"A2XS QWG8",
"A1XN 7YCY",
"A1KG 7LVX",
"ATVP M61L",
"APAW CGW2",
"AKQ3 6G7T",
"AKP0 FNF9",
"AKMJ 4F4S",
"AJAB ZRLZ",
"AGJK ZGPR",
"ADZ6 FN87",
"ABED Z2WC",
"D80R EMFN",
"D8K9 F3K3",
"DVXN 2PW0",
"DVSZ YA4R",
"D148 TQYX",
"DX3G 8EZK",
"DXNJ R0LV",
"DS3X 89TH",
"DQDH ZX0B",
"DQJ8 3WND",
"DLRD LF3M",
"DKB7 7QJ3",
"DJ7R FEF7",
"DH47 XX6Q",
"DGXR 8R7X",
"DF8K 3VF1",
"DEAL PC27",
"DCW7 83HZ",
"DCAF MKYN",
"DCK0 2JYV",
"DB79 SYDG",
"DA7W G79T",
"C7WE TVAX",
"C7AF QQYA",
"C3CG XXPM",
"C23G A7FW",
"C2M8 HSHV",
"C0T6 FKXY",
"C07L HRH3",
"C0F4 H020",
"CWCB 43YG",
"CT3X MLKR",
"CSZA EZCX",
"CPZZ MNT4",
"CMSD W073",
"CKW4 AYSV",
"CJKN 6K08",
"CG1K CN9D",
"CGGW ZRFW",
"CGNE XW07",
"CF46 N40K",
"CFLS 7L9T",
"CDQX 2ZQM",
"CCL8 29G9",
"F8NW HR8T",
"F6DV 9R7W",
"F39Z SBC2",
"F3G1 EN4A",
"F3D6 JKRH",
"F29J 1XXL",
"F000 AZ0K",
"F07K 3JZC",
"FZXQ ARPT",
"FZA9 1PCW",
"FWHL 0FFH",
"FT0N PV71",
"FNQS AL9R",
"FJSY 91TJ",
"FFZP C8MW",
"FEFH 4TV9",
"FC63 JNZ6",
"FA6A YY1J",
"E9Z0 BMKQ",
"E9XX 9T4W",
"E6SA 108W",
"E34B SXN7",
"EW1G MHQV",
"ESB4 QXC2",
"ERWT MXPH",
"ENAE X4SD",
"EMEE GFZL",
"EKKE 92LH",
"EJW1 9WE7",
"EJCW E9TJ",
"EJMF JZ3W",
"EHXC GN3C",
"EGVP LXAZ",
"EGL8 SVM1",
"EFLY ZBYC",
"EEPZ 973L",
"EBGY MS74",
"EAKP JZ98",
"H8Y4 6LYR",
"H7VB E7DV",
"H673 4SB9",
"HVC9 P0M9",
"HVCR 3Y89",
"H3ZF Q0E1",
"H1TW 0GAM",
"H16M K2MB",
"H1NQ 4BWG",
"H02E JDPK",
"HYCW WFRX",
"HW3L LRJ9",
"HQQ3 KLFA",
"HQLN Z8VQ",
"HPVV QJVG",
"HPK8 3WGR",
"HM3A Y3QJ",
"HLTH AH2R",
"HH3W HJ78",
"HEZF 7AC3",
"HAVX HP7T",
"G8Y8 214B",
"G8WK F1ZA",
"GVY6 Y8FA",
"GV7P 1BYP",
"G3Z1 JMAV",
"G3D9 RG3P",
"G3N4 GDGQ",
"GY8H LH8P",
"GYPR BFZE",
"GXT6 6VK4",
"GWF2 BYM3",
"GQ3G WRL2",
"GQKG J3KP",
"GPMZ VBQR",
"GLBZ Y2WS",
"GG46 T9FB",
"GGEF XT6P",
"GGKD K6AP",
"GFYL VWYZ",
"GFSC JCEF",
"GE1V YVHQ",
"GERS 9E7G",
"GCZC G6M9",
"GAP8 LNYC",
"K6QH 9Y7J",
"K3FL 9W9T",
"K3PB 80SA",
"K3LL BFTC",
"K1CR 3LPK",
"K0S1 8GSR",
"K04H PHE8",
"KZ4L TTFN",
"KYCG QP9E",
"KS78 2YKP",
"KQ71 06TS",
"KQRR 77JF",
"KP16 NTFL",
"KMK9 A6MW",
"KKEP R864",
"KFEY J9CJ",
"KE4R 0BST",
"KCSD M3V9",
"KCED 4TQ4",
"KADF 6D8F",
"J9HB E4SZ",
"J7GK 9YBT",
"J7EL 8PZB",
"J6B7 H2KA",
"J6LZ 6J3Q",
"JVKW KK2Z",
"J4LZ 6Z22",
"J0M3 6H21",
"J0MJ GV3Z",
"JXFV 2HDH",
"JT08 14MM",
"JRPV 8Z8X",
"JPAC EY3N",
"JNWA 4XSP",
"JMRG F4FY",
"JHXK 86ZG",
"JHD6 LG7B",
"JEJC 7BLR",
"JD8C 8BKB",
"JBT3 D6M3",
"M7XE 0M6A",
"M7K0 RCY9",
"M68X MYJA",
"M4RV B89S",
"M3KD EWFD",
"M2S1 YESB",
"M2PS FTGY",
"M1XM WZTG",
"M126 F7S3",
"M01J D890",
"MZQN SMRM",
"MXGD YSHA",
"MS8M MTTV",
"MSM1 XR1P",
"MP4L FTA4",
"MM2Y B02Y",
"MM2E 4L4V",
"MJ22 Z43L",
"MJFV VM87",
"MHYR J8Z3",
"MHBM 2K04",
"L81P EBVP",
"L8LN KNT0",
"L7X1 QF39",
"L7BX AVLL",
"LV6B VMCG",
"L3RX Y0FP",
"L2GW 4WX9",
"LZB9 LBDS",
"LX0K 699H",
"LWDD KD6V",
"LSY0 LD0F",
"LRL8 XQ4N",
"LQAT CKDE",
"LP2T FLT4",
"LP2J 014R",
"LPLK WYLM",
"LLHJ ZDK2",
"LKHA FT8S",
"LE1J 09VA",
"LDR1 PT9V",
"LBP1 8X7H",
"LATF SQLX",
"P6Z1 J40Q",
"P6CL TS6N",
"P2J7 M0LH",
"P2JM ZLM4",
"PWCW 2F4F",
"PSSA HBVE",
"PSKC PW12",
"PQGD R4PP",
"PK6J 8ZP7",
"PH1Z D7LX",
"PHKV GEXT",
"PG0E T8YZ",
"PFYF CS2B",
"PFW9 3Z68",
"PE4L B76R",
"PBWH QLKA",
"N8RK HQLH",
"N7BX 7XX0",
"N6YQ 6EB1",
"NVBC GX1W",
"N1MF 323B",
"NZGT VP27",
"NXXL 3B91",
"NWR7 CRRF",
"NTFX PRFC",
"NTML QBQS",
"NS8S J3EW",
"NS38 HD29",
"NSBD 1ZCK",
"NP4Z 4N00",
"NPD4 11Z4",
"NLMZ 9BNL",
"NJ1Y EV9H",
"NJW8 18WX",
"NEGX BVKD",
"NA29 0KS4",
"R7FD PV27",
"R7CJ SK2Z",
"R2WM 11BE",
"R24X 86MA",
"R1BY NJ28",
"R1MH A4D3",
"RZD7 QP13",
"RXZZ 2RCQ",
"RSSZ BB7H",
"RR6Z WFDD",
"RRJP 216Q",
"RQZ1 9XW9",
"RNZN 639M",
"RMXQ E78D",
"RMHF 092P",
"RLWT DZ6X",
"RKRM 9S33",
"RG6F 9DXS",
"RGF8 6J2C",
"RGJB 42GS",
"RFSP AVXG",
"RBFQ J36A",
"RBJ8 JB16",
"Q8W2 3BCX",
"Q8SG AYL9",
"Q4BB 6N3X",
"Q3P9 B291",
"Q2Z1 WCV3",
"Q2DT 0PR7",
"Q2LT 1KRL",
"QZ9X 7VLG",
"QYFB PYT4",
"QX6H DFAK",
"QWDZ GTB3",
"QWQF FY87",
"QSXL 0R11",
"QS9X WQ93",
"QGXW 8HT7",
"QG44 ZXMG",
"QDRB J0PT",
"T98Q 2B3B",
"T7QP ZZ36",
"T6CN RMF3",
"T2E2 QN1D",
"TZF6 K6WL",
"TZJP TQJY",
"TT9E GWHC",
"TS0A 4DQ2",
"TSPT 42CY",
"TPVE BE4L",
"TNZS Q130",
"TK1Y H2BY",
"THEJ A4ZV",
"THA4 GBR0",
"TFDA RB3V",
"TAXJ 1LGN",
"TARB STR3",
"S9SE JHW0",
"S87T X7R0",
"S8DE KGY4",
"S71V WJHM",
"S6E3 Q0LK",
"SVSK L9JY",
"SVHC JC7V",
"SVL4 0SZN",
"S23E VX6A",
"S1EP XTBB",
"S1L9 YCBY",
"S02K 97K7",
"S0P9 QD3J",
"SZVY ZZ1C",
"SYN2 T33Y",
"SXP6 0NP4",
"STKL MSBN",
"SS7Q NHTJ",
"SR4Q N9WE",
"SQVV G8D6",
"SN3L J1AG",
"SNFV BX9Z",
"SNKE EG0S",
"SMEB 4D8L",
"SJXR D4WK",
"SHLB GEDV",
"SEML VDEX",
"X9E2 0TF1",
"X7E3 Q78H",
"X7BH 7YGV",
"XV7Y 1RG4",
"XV3S XG6S",
"X38Q R80N",
"X33T XB0Q",
"X2WS FMQ7",
"X24X 8DMP",
"XYKX 9YMW",
"XQBK 6AKG",
"XQKC 2A7Y",
"XPJ2 WZAF",
"XL6Y 00Q9",
"XLC0 H4JN",
"XG3Q 0R19",
"XE4A 8P0C",
"XDC0 DWZL",
"XCR1 2339",
"XB1X T83E",
"W9GT TZ3A",
"W8S6 3RZY",
"W6T8 PKHQ",
"W6JN H6PZ",
"W4JA G8J7",
"W1XX Z61L",
"W0TG 042K",
"W03R AF1V",
"W0HB FXHE",
"W0GJ PGV6",
"WW3P H3KJ",
"WWH3 LHGE",
"WTX0 V4PG",
"WRGZ E2HL",
"WPZA 7L33",
"WPL2 ASVB",
"WN2Q 194Z",
"WMKW SHY9",
"WJT4 M8TJ",
"WJFH YSTJ",
"WJFG W4QY",
"WFTE VQZX",
"WEY4 0FZR",
"WEYJ CK0S",
"WC7Y H9M7",
"WB9X 78ET",
"WA1Z Q470",
"WA41 X18T",
"Z87H V1HA",
"Z747 P8FL",
"Z6CQ M93B",
"Z3ZP W06A",
"Z3JN Y8JP",
"Z2W9 CVLK",
"Z0GL 8PKM",
"ZYV2 E4RL",
"ZWEH WAD2",
"ZWNW GYFA",
"ZS9M 9YPK",
"ZSAA 8FPW",
"ZQP1 GR1B",
"ZP6E WSS7",
"ZNA3 Z1EH",
"ZLLF TTXJ",
"ZJDJ B8HF",
"ZHB0 WPG2",
"ZF1P 6EDA",
"ZFR9 24EY",
"Y8T8 3WQR",
"Y84C J2RJ",
"YVGA WQ7L",
"Y4RA NKWZ",
"Y36M K9HB",
"Y3N2 QTLG",
"Y2MB M973",
"Y16J 0DYS",
"Y09E VWAF",
"YZY8 VFPS",
"YY3G BC3K",
"YX1B VDDH",
"YWB1 ZRG1",
"YRAL VY4V",
"YQ60 CTPE",
"YNSY G0RW",
"YLGL BJEJ",
"YKRB GGQT",
"YJFB W16W",
"YJD0 WKCA",
"YF42 Z6QD",
"YFGT XYNL",
"YEQS CL9X",
"YD7H 2TF1",
"YDV2 PW2Z",
"YBP9 2Z4N",
"1VAE JE8A",
"14TF 29R9",
"10HJ EYKY",
"1Z6D 6PVY",
"1WWG S0S6",
"1SV9 DMLH",
"1SBC W4X2",
"1R7V YLE8",
"1REN ALK2",
"1PRW 3P8M",
"1M93 FZQ1",
"08X7 6497",
"07N2 0M2D",
"032B Z40Q",
"026C 7L4B",
"01F8 S3Y2",
"0071 N6TS",
"0ZZ2 4N6V",
"0ZWA GEFA",
"0Z29 WR6Z",
"0YW7 PJEG",
"0WZX 6A7A",
"0NGK XB37",
"0LDV F768",
"0H6T F0JV",
"0ELK YCSR",
"0DZW L3AG",
"0CM6 6TGP",
"38KP FGPK",
"3766 4VAE",
"37GN ACVF",
"36SS 0QKB",
"3638 3LSQ",
"3YPP ZE68",
"3TSL PNS2",
"3S70 93NY",
"3R47 0NRT",
"3RNT Z6NX",
"3QM2 Y8DL",
"3QJA 067Z",
"3NMK M7M2",
"3JNJ MBFG",
"3FBT E4FP",
"2V9Z A0FT",
"2VR0 CJDX",
"23RQ GHP3",
"2XKB KS6B",
"2WEW 22XM",
"2NK8 2ZQZ",
"2MG1 G44M",
"2L9W C7HY",
"2KGP KWSA",
"2JE8 YPCA",
"2H0V KD92",
"2B13 3G0Y",
"2BNR Z19K",
"V8Y4 JNFZ",
"V879 09P9",
"V7TM S0HK",
"V7NB PXSL",
"VZWE F60K",
"VT0E JNVC",
"VPGB PKG2",
"VNF4 8FGM",
"VK7S RZYC",
"VKA3 2L30",
"VH1C D12M",
"VFKV 4KNW",
"VCH1 LY0S",
"46DZ REKK",
"4V1L 49G2",
"4VJB HTEN",
"416S R8VQ",
"409Z Q4H1",
"4Y7W FZ87",
"4X7H 663W",
"4XR0 RDD3",
"4XQY YT8K",
"4WWS KNXY",
"4TV7 D0HJ",
"4SDP M4KG",
"4PPS 208G",
"4N9K F8P1",
"4NCN NC6J",
"4KT2 3CM2",
"4E1L HCY4",
"4BD0 W9NW",
"4BCN 2Q0T",
"4A23 ZEHR",
"788E 2M6Y",
"78CJ 732Y",
"761M QXLJ",
"7400 NQKX",
"7044 6WHY",
"7Z12 MXZQ",
"7ZYX 222W",
"7ZTA K8SN",
"7ZGR D8X7",
"7W7V 8TSP",
"7Q6A X8S2",
"7NW4 KS6D",
"7GN1 SQQM",
"7DGG DKLF",
"7AV3 P3YT",
"69B8 MQ8P",
"68X2 Q43T",
"68HP QC6G",
"6232 ZL6P",
"62PM 0J18",
"61P4 YNEA",
"60MC AGGP",
"6Z4V EB81",
"6ZD3 AX34",
"6Y6K 98K7",
"6WFS 9F4V",
"6TZZ 8YP0",
"6T7P RF1H",
"6T4E MQGZ",
"6RFP GP9C",
"6QVA WJAK",
"6QMN TY32",
"6PH3 WF1N",
"6N2T KXBY",
"6MZW Z97N",
"6K0V L9M0",
"6J89 VYVA",
"6H6E TVA4",
"6G6F WGJV",
"6E4P 3W3Z",
"6C1G 2Z8S",
"6CA1 ANSK",
"6BB3 31NW",
"6AED 0GJD",
"996T B9ZF",
"98E2 RZJB",
"97PT TCTE",
"96JT ANG3",
"9Z8L 14M2",
"9Y2Y 0TLJ",
"9YQQ WL0K",
"9YL2 RSTY",
"9XR0 89HP",
"9XQ6 V3AA",
"9WRW B3AT",
"9WLM YRZA",
"9QGY CPFQ",
"9P4W MSSC",
"9PND HE4H",
"9J9A VAVE",
"9JMC J04V",
"9F11 G036",
"9FVZ TZP7",
"9FFE K2TH",
"9FQE RPRR",
"9EXY 17EW",
"87ZC KBSY",
"8V3E FNPG",
"8VAH JKVV",
"8312 FWJB",
"83YT D72G",
"83CP BVQF",
"821C C2KR",
"82AE QYJY",
"81EV QE3P",
"8ZCW LDMM",
"8YX7 86PL",
"8XFB G7CX",
"8WWR 3KP3",
"8WLQ CBF2",
"8TXZ GZ8Q",
"8TS2 ZE3F",
"8T48 9SJJ",
"8TRR 1PRA",
"8SNS A9JC",
"8L7K 1EVA",
"8KEW M1TN",
"8J7Q QSDL",
"8JFK PGPX",
"8JQJ 8LBT",
"8HNQ 8VD2",
"8GQR EVV0",
"8FZE 2ZYG",
"8F30 QDP3",
"8EWF V9Q3",
"8EDV X3BV",
"8ERE BZ8W",
"8A18 32TC"
}

function finder:post_start()
	if kill then return end

	local p=Isaac.GetPlayer(0)
	local dps = p.Damage * (30 / (p.MaxFireDelay + 1))
	
	function finder:check_room_items()
		local lst=Game():GetRoom():GetEntities()
		for i=0, lst.Size-1 do
			if lst:Get(i).Type==5 and lst:Get(i).Variant==390 then -- mom's chest
				lst:Get(i):ToPickup():TryOpenChest()
				break
			end
		end
		lst=Game():GetRoom():GetEntities()
		for i=0, lst.Size-1 do
			if lst:Get(i).Type==5 and lst:Get(i).Variant==100 then -- item
				-- print(lst:Get(i).SubType)
				if lst:Get(i).SubType==114 then -- mom's knife
					return false
				end
			end
		end
		return true
	end
	
	Isaac.ExecuteCommand("stage 13")
	Game():GetLevel():ChangeRoom(82) -- mom's bedroom ID
	if finder:check_room_items() then goto R; end
	
	print(Seeds.Seed2String(Game():GetSeeds():GetStartSeed()) .. " : " .. dps)
		
	::R::
	r=true
end

function finder:post_update()
	if r then
		r=false
		current = current + 1
		if current > #seeds_list then
			return
		end
		Isaac.ExecuteCommand("seed " .. seeds_list[current])
	end
	
	if Input.IsButtonPressed(Keyboard.KEY_T, 0) then
		kill = false
		current = 1
		Isaac.ExecuteCommand("seed " .. seeds_list[1])
	end
	
	if Input.IsButtonPressed(Keyboard.KEY_Y, 0) then
		kill = true
	end
end

finder:AddCallback(ModCallbacks.MC_POST_GAME_STARTED,finder.post_start)
finder:AddCallback(ModCallbacks.MC_POST_UPDATE,finder.post_update)
