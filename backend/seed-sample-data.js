const sqlite3 = require('sqlite3').verbose();

const db = new sqlite3.Database('./fridge.db', (err) => {
  if (err) {
    console.error('Error opening database:', err);
    process.exit(1);
  }
  console.log('Connected to database');
});

// Calculate expiry date (days from today)
function getExpiryDate(daysFromNow) {
  const date = new Date();
  date.setDate(date.getDate() + daysFromNow);
  return date.toISOString().split('T')[0];
}

// Sample ingredients matching the lofi UI prototype
const sampleIngredients = [
  { name: 'tomato', category: 'vegetable', quantity: 2, unit: 'pieces', expiry_date: getExpiryDate(2) },
  { name: 'apple', category: 'fruit', quantity: 1, unit: 'pieces', expiry_date: getExpiryDate(2) },
  { name: 'grapes', category: 'fruit', quantity: 10, unit: 'pieces', expiry_date: getExpiryDate(3) },
  { name: 'carrot', category: 'vegetable', quantity: 1, unit: 'pieces', expiry_date: getExpiryDate(3) },
  { name: 'garlic', category: 'vegetable', quantity: 5, unit: 'cloves', expiry_date: getExpiryDate(7) },
  { name: 'olive oil', category: 'condiment', quantity: 1, unit: 'bottle', expiry_date: getExpiryDate(90) },
];

// Clear existing ingredients
db.run('DELETE FROM ingredients', (err) => {
  if (err) {
    console.error('Error clearing ingredients:', err);
    return;
  }
  console.log('Cleared existing ingredients');

  // Insert sample ingredients
  let inserted = 0;
  sampleIngredients.forEach((ingredient) => {
    db.run(
      'INSERT INTO ingredients (name, category, quantity, unit, expiry_date) VALUES (?, ?, ?, ?, ?)',
      [ingredient.name, ingredient.category, ingredient.quantity, ingredient.unit, ingredient.expiry_date],
      (err) => {
        if (err) {
          console.error('Error inserting ingredient:', err);
          return;
        }
        inserted++;
        console.log(`Added: ${ingredient.name} (expires in ${ingredient.expiry_date})`);

        if (inserted === sampleIngredients.length) {
          console.log('\nSample data seeding complete!');
          console.log(`Total ingredients: ${inserted}`);
          db.close();
        }
      }
    );
  });
});
