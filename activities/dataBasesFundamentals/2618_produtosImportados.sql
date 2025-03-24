SELECT products.name, providers.name, categories.name
FROM products

WHERE providers.name = 'Sansul SA' AND categories.name = 'Imported';