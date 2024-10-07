# Online Retail Store Database Schema

## Table Relationships

```
+-------------------+
|      users        |
|-------------------|
| id (PK)           |
| username          |
| email             |
| password          |
| created_at        |
+-------------------+
          |
          | 1
          |
          | n
          v
+-------------------+
|      orders       |
|-------------------|
| id (PK)           |
| user_id (FK)     |
| total_amount      |
| created_at        |
+-------------------+
          |
          | 1
          |
          | n
          v
+-------------------+
|   order_items     |
|-------------------|
| id (PK)           |
| order_id (FK)    |
| product_id (FK)  |
| quantity          |
| price             |
+-------------------+
          ^
          | n
          |
          | 1
+-------------------+
|     products      |
|-------------------|
| id (PK)           |
| name              |
| description       |
| price             |
| stock_quantity    |
| created_at        |
+-------------------+
```

## Explanation of Relationships

1. **Users to Orders**:
   - A user can have multiple orders (`1 to n` relationship).
   - The `orders` table includes a foreign key `user_id` referencing the `id` in the `users` table.

2. **Orders to Order Items**:
   - An order can contain multiple order items (`1 to n` relationship).
   - The `order_items` table includes a foreign key `order_id` referencing the `id` in the `orders` table.

3. **Products to Order Items**:
   - A product can be included in multiple order items across different orders (`1 to n` relationship).
   - The `order_items` table also includes a foreign key `product_id` referencing the `id` in the `products` table.

### Summary

- **Users** have multiple **Orders**.
- Each **Order** can consist of multiple **Order Items**.
- Each **Order Item** refers to a single **Product**.
