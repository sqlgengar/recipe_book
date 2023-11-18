-- Mostrar las categorias que son principales.
SELECT
            C.id as 'id_category',
            C.name as 'name_category'
FROM
            categories C
WHERE
            C.id_daddy = 0
            AND
            C.status = 1
            AND
            C.name != ''
ORDER BY
            C.id ASC
LIMIT
            100
;

-- Mostrar los recetas y las categorias a las que pertenecen.
SELECT
            R.id as 'id_recipe',
            R.name as 'name_recipe',
            C.id as 'id_category',
            C.name as 'name_category'
FROM
            recipes R,
            recipe_categories RC,
            categories C
WHERE
            R.id = RC.id_recipe
            AND
            RC.id_category = C.id
            AND
            R.status = 1
            AND
            R.name != ''
            AND
            RC.status = 1
            AND
            C.status = 1
            AND
            C.name != ''
ORDER BY
            R.id ASC,
            C.id ASC
LIMIT
            500
;

-- Mostrar todos los ingredientes con sus unidades asociadas.
SELECT
            I.id as 'id_ingredient',
            I.name as 'name_ingredient',
            ( SELECT U.id FROM units U WHERE U.id = I.id_unit LIMIT 1 ) as 'id_unit',
            ( SELECT U.unit FROM units U WHERE U.id = I.id_unit LIMIT 1 ) as 'unit',
            ( SELECT U.name FROM units U WHERE U.id = I.id_unit LIMIT 1 ) as 'name_unit'
FROM
            ingredients I
WHERE
            I.status = 1
            AND
            I.name != ''
ORDER BY
            I.id ASC
LIMIT
            1000
;

-- Mostrar solo recetas creadas por Gordon Ramsay, de duration menor o igual a 15 minutos, que sean de level easy, que rinda mas de 4 porciones, con score superior o igual a 7, actualizadas en los ultimos 7 dias.
SET @MAIL = ( SELECT U.email FROM users U WHERE U.name = 'Gordon Ramsay' AND U.status = 1 LIMIT 1 );

SELECT
            R.id as 'id_recipe',
            R.name as 'name_recipe',
            R.preparation as 'preparation_recipe'
FROM
            recipes R
WHERE
            ( SELECT 1 FROM users U WHERE U.id = R.id_user AND U.email = @MAIL LIMIT 1 )
            AND
            R.duration <= 15
            AND
            R.level = 'EASY'
            AND
            R.parts > 4
            AND
            R.score >= 7
            AND
            R.date_update BETWEEN DATE_SUB( NOW(), INTERVAL 7 DAY ) AND NOW()
            AND
            R.status = 1
ORDER BY
            R.id ASC
LIMIT
            25
;

-- Mostrar las 3 recetas con mayor cantidad de usuarios que las matarios como favoritos, y su score.
SELECT
            COUNT( RF.id_recipe ) as 'amount_favorites',
            RF.id as 'id_recipe',
            R.name as 'name_recipe',
            R.score as 'score_recipe'
FROM
            recipes R,
            recipe_favorites RF
WHERE
            R.id = RF.id_recipe
            AND
            R.status = 1
            AND
            RF.status = 1
GROUP BY
            RF.id_recipe
ORDER BY
            amount_favorites DESC
LIMIT
            3
;

-- Mostrar recetas con los ingredientes que tiene y las medidas que se utilisan.
SELECT
            R.id as 'id_recipe',
            R.name as 'name_recipe',
            I.name as 'name_ingredient',
            CONCAT( RI.amount, ' ', ( SELECT U.unit FROM units U WHERE U.id = I.id_unit LIMIT 1 ) ) as 'consume'
FROM
            recipes R,
            recipe_ingredients RI,
            ingredients I
WHERE
            R.id = RI.id_recipe
            AND
            RI.id_ingredient = I.id
            AND
            R.status = 1
            AND
            RI.status = 1
            AND
            I.status = 1
ORDER BY
            RI.id_recipe ASC,
            RI.id_ingredient ASC
LIMIT
            2000
;

-- Mostrar listado de usuarios Admin activos.
SET @ID_ADMIN = ( SELECT R.id FROM roles R WHERE R.name = 'Admin' AND R.status = 1 LIMIT 1 );

SELECT
            U.id as 'id_user',
            U.name as 'name user',
            U.email as 'email_user'
FROM
            users U,
            roles R
WHERE
            U.id_rol = R.id
            AND
            U.status = 1
            AND
            R.id = @ID_ADMIN
ORDER BY
            U.id ASC
LIMIT
            25
;