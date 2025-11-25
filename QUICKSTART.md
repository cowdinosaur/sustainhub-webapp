# Quick Start Guide

Get up and running in 5 minutes!

## 1. Install Dependencies

```bash
# Install backend dependencies
cd backend
npm install

# Install frontend dependencies
cd ../frontend
npm install
```

## 2. Start the Backend

Open a terminal and run:

```bash
cd backend
npm start
```

You should see:
```
Server is running on http://localhost:3001
Connected to SQLite database
```

## 3. Add Sample Data (Optional but Recommended)

Open another terminal and run:

```bash
cd backend
npm run seed
```

This adds sample ingredients like tomato, apple, grapes, etc.

## 4. Start the Frontend

Open another terminal and run:

```bash
cd frontend
npm run dev
```

Look for the URL (usually `http://localhost:5173`) and open it in your browser.

## 5. Explore the App

You should now see:
- **Cover Page** - Landing page with buttons
- **Inventory** - View your ingredients and expiry dates
- **Meal Ideas** - Get recipe suggestions based on your ingredients
- **Recipe Details** - View complete recipes with instructions

## Testing ESP32 Integration

To test the API that your ESP32 will use:

```bash
cd backend
npm run test-api
```

## Next Steps

- Check out the [README.md](README.md) for full documentation
- Modify the API endpoints for your ESP32 code
- Customize the recipes in `backend/server.js`
- Adjust the styling to match your preferences

## Troubleshooting

**"Port 3001 already in use"**
- Change the PORT in `backend/.env` to a different number

**"Cannot connect to backend"**
- Make sure the backend is running on http://localhost:3001
- Check if there are any error messages in the backend terminal

**"No recipes showing"**
- Run `npm run seed` in the backend directory to add sample data
- Make sure you have ingredients in your database

## File Structure at a Glance

```
sustainhub_webapp/
├── backend/
│   ├── server.js              # Main API server
│   ├── seed-sample-data.js    # Sample data script
│   ├── test-esp32-api.js      # ESP32 API test
│   └── fridge.db              # Database (auto-generated)
├── frontend/
│   ├── src/
│   │   ├── pages/            # React page components
│   │   └── App.jsx           # Main app
│   └── index.html
└── README.md                  # Full documentation
```

Happy coding!
