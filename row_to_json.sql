DROP PROCEDURE IF EXISTS ROW_TO_JSON;

CREATE PROCEDURE ROW_TO_JSON (
	IN _table_name VARCHAR(64),
	IN _id_column_name VARCHAR(32),
	IN _id_value VARCHAR(32)
) BEGIN
	SET @JSON_PRAM = (SELECT GROUP_CONCAT(CONCAT("'", column_name, "',", column_name)) FROM information_schema.columns WHERE table_name = "railink_lcl_cabin");
	
	SET @SELECT_JSON_STMT = CONCAT("SELECT JSON_OBJECT(", @JSON_PRAM, ") FROM ",_table_name, " WHERE ", _id_column_name, " = '", _id_value, "'");
	PREPARE SELECT_JSON_STMT FROM @SELECT_JSON_STMT;
	EXECUTE SELECT_JSON_STMT;
	DEALLOCATE PREPARE SELECT_JSON_STMT;
END;

CALL ROW_TO_JSON("railink_lcl_cabin", "id", "RL19032000001");



