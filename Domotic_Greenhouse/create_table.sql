CREATE TABLE IF NOT EXISTS `greenhouse` (
  `id` int(11) NOT NULL,
  `date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `temp` float NOT NULL,
  `umid` float NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;