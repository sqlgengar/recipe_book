-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Servidor: mysql:3306
-- Tiempo de generación: 18-11-2023 a las 03:21:43
-- Versión del servidor: 10.5.21-MariaDB-1:10.5.21+maria~ubu2004
-- Versión de PHP: 8.2.8

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de datos: `recipe_book`
--
CREATE DATABASE IF NOT EXISTS `recipe_book` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
USE `recipe_book`;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `categories`
--

DROP TABLE IF EXISTS `categories`;
CREATE TABLE IF NOT EXISTS `categories` (
  `id` int(10) NOT NULL AUTO_INCREMENT COMMENT 'Primary',
  `id_daddy` int(10) NOT NULL DEFAULT 0 COMMENT 'categories.id(0:Superior)',
  `name` varchar(80) NOT NULL COMMENT 'Nombre Categoria',
  `date` timestamp NOT NULL DEFAULT current_timestamp() COMMENT 'Fecha de alta',
  `status` tinyint(1) NOT NULL DEFAULT 1 COMMENT 'Validacion',
  PRIMARY KEY (`id`),
  KEY `id_daddy` (`id_daddy`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci COMMENT='---| Categorias |---';

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `ingredients`
--

DROP TABLE IF EXISTS `ingredients`;
CREATE TABLE IF NOT EXISTS `ingredients` (
  `id` int(10) NOT NULL AUTO_INCREMENT COMMENT 'Primary',
  `id_unit` int(10) NOT NULL COMMENT 'units.id',
  `name` varchar(80) NOT NULL COMMENT 'Nombre ingrediente',
  `date` timestamp NOT NULL DEFAULT current_timestamp() COMMENT 'Fecha de alta',
  `status` tinyint(1) NOT NULL DEFAULT 1 COMMENT 'Validacion',
  PRIMARY KEY (`id`),
  KEY `id_unit` (`id_unit`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci COMMENT='---| Ingredientes |---';

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `recipes`
--

DROP TABLE IF EXISTS `recipes`;
CREATE TABLE IF NOT EXISTS `recipes` (
  `id` int(10) NOT NULL AUTO_INCREMENT COMMENT 'Primary',
  `id_user` int(10) NOT NULL COMMENT 'users.id',
  `name` varchar(80) NOT NULL COMMENT 'Nombre receta',
  `duration` int(10) DEFAULT NULL COMMENT 'Tiempo estimado en minutos para hacer la receta',
  `level` enum('EASY','MEDIUM','HARD','') NOT NULL DEFAULT 'EASY' COMMENT 'Nivel de dificultad de la receta',
  `parts` int(10) DEFAULT NULL COMMENT 'Porciones que rinde la receta',
  `preparation` longtext DEFAULT NULL COMMENT 'Script receta',
  `image` varchar(100) DEFAULT NULL COMMENT 'Path imagen receta',
  `score` int(10) DEFAULT NULL COMMENT 'Puntacion receta',
  `date_update` date DEFAULT NULL COMMENT 'Fecha de actualizacion',
  `date` timestamp NOT NULL DEFAULT current_timestamp() COMMENT 'Fecha de alta',
  `status` tinyint(1) NOT NULL DEFAULT 1 COMMENT 'Validación',
  PRIMARY KEY (`id`),
  KEY `id_user` (`id_user`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci COMMENT='---| Recetas |---';

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `recipe_categories`
--

DROP TABLE IF EXISTS `recipe_categories`;
CREATE TABLE IF NOT EXISTS `recipe_categories` (
  `id` int(10) NOT NULL AUTO_INCREMENT COMMENT 'Primary',
  `id_recipe` int(10) NOT NULL COMMENT 'recipes.id',
  `id_category` int(10) NOT NULL COMMENT 'categories.id',
  `date` timestamp NOT NULL DEFAULT current_timestamp() COMMENT 'Fecha de alta',
  `status` tinyint(1) NOT NULL DEFAULT 1 COMMENT 'Validacion',
  PRIMARY KEY (`id`),
  KEY `id_recipe` (`id_recipe`),
  KEY `id_category` (`id_category`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci COMMENT='---| Relacion recetas-categorias |---';

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `recipe_favorites`
--

DROP TABLE IF EXISTS `recipe_favorites`;
CREATE TABLE IF NOT EXISTS `recipe_favorites` (
  `id` int(10) NOT NULL AUTO_INCREMENT COMMENT 'Primary',
  `id_recipe` int(10) NOT NULL COMMENT 'recipes.id',
  `id_user` int(10) NOT NULL COMMENT 'users.id',
  `date` timestamp NOT NULL DEFAULT current_timestamp() COMMENT 'Fecha de alta',
  `status` tinyint(1) NOT NULL DEFAULT 1 COMMENT 'Validacion',
  PRIMARY KEY (`id`),
  KEY `id_recipe` (`id_recipe`),
  KEY `id_user` (`id_user`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci COMMENT='---| Recetas favoritas de usuarios |---';

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `recipe_ingredients`
--

DROP TABLE IF EXISTS `recipe_ingredients`;
CREATE TABLE IF NOT EXISTS `recipe_ingredients` (
  `id` int(10) NOT NULL AUTO_INCREMENT COMMENT 'Primary',
  `id_recipe` int(10) NOT NULL COMMENT 'recipes.id',
  `id_ingredient` int(10) NOT NULL COMMENT 'ingredients.id',
  `amount` decimal(15,2) NOT NULL COMMENT 'Cantidad del ingrediente en la receta',
  `date` timestamp NOT NULL DEFAULT current_timestamp() COMMENT 'Fecha de alta',
  `status` tinyint(1) NOT NULL DEFAULT 1 COMMENT 'Validacion',
  PRIMARY KEY (`id`),
  KEY `id_recipe` (`id_recipe`),
  KEY `id_ingredient` (`id_ingredient`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci COMMENT='---| Relacion recetas-ingredientes |---';

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `roles`
--

DROP TABLE IF EXISTS `roles`;
CREATE TABLE IF NOT EXISTS `roles` (
  `id` int(10) NOT NULL AUTO_INCREMENT COMMENT 'Primary',
  `name` varchar(80) NOT NULL COMMENT 'Nombre rol',
  `date` timestamp NOT NULL DEFAULT current_timestamp() COMMENT 'Fecha de alta',
  `status` tinyint(1) NOT NULL DEFAULT 1 COMMENT 'Validacion',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci COMMENT='---| Roles de usuarios |---';

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `units`
--

DROP TABLE IF EXISTS `units`;
CREATE TABLE IF NOT EXISTS `units` (
  `id` int(10) NOT NULL AUTO_INCREMENT COMMENT 'Primary',
  `unit` char(5) NOT NULL COMMENT 'Letra ID para unidad',
  `name` varchar(80) NOT NULL COMMENT 'Nombre unidad',
  `date` timestamp NOT NULL DEFAULT current_timestamp() COMMENT 'Fecha de alta',
  `status` tinyint(1) NOT NULL DEFAULT 1 COMMENT 'Validacion',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci COMMENT='---| Unidades |---';

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `users`
--

DROP TABLE IF EXISTS `users`;
CREATE TABLE IF NOT EXISTS `users` (
  `id` int(10) NOT NULL AUTO_INCREMENT COMMENT 'Primary',
  `id_rol` int(10) NOT NULL DEFAULT 1 COMMENT 'roles.id',
  `name` varchar(80) NOT NULL COMMENT 'Nombre rol',
  `email` varchar(80) NOT NULL COMMENT 'Correo Electronico',
  `pass` varchar(80) NOT NULL COMMENT 'Contraseña Encriptada',
  `date` timestamp NOT NULL DEFAULT current_timestamp() COMMENT 'Fecha de alta',
  `status` tinyint(1) NOT NULL DEFAULT 1 COMMENT 'Validacion',
  PRIMARY KEY (`id`),
  UNIQUE KEY `email` (`email`),
  KEY `id_rol` (`id_rol`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci COMMENT='---| Usuarios |---';
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
