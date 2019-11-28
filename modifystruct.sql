use hotelmis;
alter table t_beforerep modify rep_num float NOT NULL default '0';
alter table t_behindrep modify rep_num float NOT NULL default '0';
alter table t_inoutrep modify food_num float NOT NULL default '0',modify t_num float NOT NULL default '0';