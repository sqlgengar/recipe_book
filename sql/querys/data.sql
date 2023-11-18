USE recipe_book;

-- Recetas
TRUNCATE recipes;
INSERT INTO recipes
(id_user, name, duration, level, parts, preparation, image, score, date)
VALUES
(FLOOR(1 + RAND() * 2), 'Pasta Carbonara', 30, 2, 4, 'Cocinar la pasta y mezclar con una salsa de huevo, queso parmesano y panceta.', CONCAT( './images/', SUBSTRING(MD5(RAND()) FROM 1 FOR 10), '.jpg' ), FLOOR(1 + RAND() * 10), NOW()),
(FLOOR(1 + RAND() * 2), 'Ensalada César', 15, 1, 2, 'Preparar lechuga, crutones, pollo a la parrilla y aderezo de anchoas.', CONCAT( './images/', SUBSTRING(MD5(RAND()) FROM 1 FOR 10), '.jpg' ), FLOOR(1 + RAND() * 10), NOW()),
(FLOOR(1 + RAND() * 2), 'Tacos de Carnitas', 60, 3, 6, 'Cocinar la carne de cerdo lentamente con especias y servir en tortillas de maíz con cebolla y cilantro.', CONCAT( './images/', SUBSTRING(MD5(RAND()) FROM 1 FOR 10), '.jpg' ), FLOOR(1 + RAND() * 10), NOW()),
(FLOOR(1 + RAND() * 2), 'Risotto de Champiñones', 45, 2, 3, 'Cocinar arroz con caldo de champiñones, agregar champiñones salteados y queso parmesano.', CONCAT( './images/', SUBSTRING(MD5(RAND()) FROM 1 FOR 10), '.jpg' ), FLOOR(1 + RAND() * 10), NOW()),
(FLOOR(1 + RAND() * 2), 'Pastel de Chocolate', 60, 3, 8, 'Hornear un pastel de chocolate con glaseado de vainilla y decorar con fresas.', CONCAT( './images/', SUBSTRING(MD5(RAND()) FROM 1 FOR 10), '.jpg' ), FLOOR(1 + RAND() * 10), NOW())
;

-- Categorias
TRUNCATE categories;
INSERT INTO categories
( id_daddy, name, date)
VALUES
(0, 'Comida Principal', NOW()),
(0, 'Postres', NOW()),
(1, 'Pasta', NOW()),
(1, 'Ensaladas', NOW()),
(4, 'Tartas', NOW())
;

-- Roles
TRUNCATE roles;
INSERT INTO roles
(name, date)
VALUES
('Visualizador', NOW()),
('Admin', NOW())
;

-- Unidades
TRUNCATE units;
INSERT INTO units
(unit, name, date)
VALUES
('g', 'Gramos', NOW()),
('ml', 'Mililitros', NOW()),
('taza', 'Tazas', NOW()),
('u', 'Unidades', NOW())
;

-- Ingredientes
TRUNCATE ingredients;
INSERT INTO ingredients
(id_unit, name, date)
VALUES
(1, 'Pasta', NOW()),
(1, 'Panceta', NOW()),
(2, 'Huevo', NOW()),
(1, 'Queso Parmesano', NOW()),
(2, 'Aderezo de Anchoas', NOW()),
(1, 'Crutones', NOW()),
(1, 'Pechugas de Pollo', NOW()),
(2, 'Queso Parmesano Rallado', NOW()),
(1, 'Lechuga', NOW()),
(1, 'Carne de Cerdo', NOW()),
(2, 'Cebolla', NOW()),
(2, 'Cilantro', NOW()),
(2, 'Salsa de Tomate', NOW()),
(1, 'Arroz', NOW()),
(1, 'Champiñones', NOW()),
(2, 'Queso Parmesano', NOW()),
(2, 'Caldo de Champiñones', NOW()),
(1, 'Harina', NOW()),
(1, 'Azúcar', NOW()),
(1, 'Aceite de Oliva', NOW()),
(2, 'Huevo', NOW()),
(1, 'Chocolate', NOW())
;

-- Relacion entre recetas y categorias
TRUNCATE recipe_categories;
INSERT INTO recipe_categories
(id_recipe, id_category, date)
VALUES
(1, 1, NOW()),
(2, 2, NOW()),
(3, 3, NOW()),
(4, 4, NOW()),
(5, 5, NOW()),
(2, 1, NOW())
;

-- Recetas favoritas
TRUNCATE recipe_favorites;
INSERT INTO recipe_favorites
(id_recipe, id_user, date )
VALUES
(FLOOR(1 + RAND() * 5), FLOOR(1 + RAND() * 5), NOW()),
(FLOOR(1 + RAND() * 5), FLOOR(1 + RAND() * 5), NOW()),
(FLOOR(1 + RAND() * 5), FLOOR(1 + RAND() * 5), NOW())
;

-- Relacion entre recetas e ingredientes
TRUNCATE recipe_ingredients;
INSERT INTO recipe_ingredients
(id_recipe, id_ingredient, amount, date)
VALUES
(1, 1, 300, NOW()),
(1, 2, 150, NOW()),
(1, 3, 3, NOW()),
(1, 4, 50, NOW()),
(2, 5, 1, NOW()),
(2, 6, 2, NOW()),
(2, 7, 2, NOW()),
(2, 8, 1, NOW()),
(2, 9, 1, NOW()),
(3, 10, 500, NOW()),
(3, 11, 1, NOW()),
(3, 12, 1, NOW()),
(3, 13, 1, NOW()),
(4, 14, 300, NOW()),
(4, 15, 500, NOW()),
(4, 16, 1, NOW()),
(4, 17, 1, NOW()),
(5, 18, 200, NOW()),
(5, 19, 150, NOW()),
(5, 20, 100, NOW()),
(5, 21, 3, NOW()),
(5, 22, 200, NOW())
;

-- Usuarios
TRUNCATE users;
INSERT INTO users
(id_rol, name, email, pass, date)
VALUES
(2, 'Aye', 'aye@example.com', MD5(RAND()), NOW()),
(2, 'Gordon Ramsay', 'gordon@example.com', MD5(RAND()), NOW()),
(1, 'Julia Child', 'julia@example.com', MD5(RAND()), NOW()),
(1, 'Jamie Oliver', 'jamie@example.com', MD5(RAND()), NOW()),
(1, 'Anthony Bourdain', 'anthony@example.com', MD5(RAND()), NOW()),
(1, 'Nigella Lawson', 'nigella@example.com', MD5(RAND()), NOW())
;